#include <linux/version.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/device.h>

#include <linux/timer.h>

#include <asm/cacheflush.h>
//#include <asm/arch/am_regs.h>
#include <mach/am_regs.h>

#include "dsp_mailbox.h"
#include "dsp_codec.h"

int dsp_mailbox_send(struct audiodsp_priv *priv,int overwrite,int num,int cmd,const char *data,int len)
{
	unsigned long flags;
	int res=-1;
	struct mail_msg *m;
	m=&priv->mailbox_reg2[num];

	local_irq_save(flags);
	if(overwrite || m->status==0)
		{
			
			m->cmd=cmd;
			m->data=(char *)data;
			m->len=len;
			m->status=1;
			after_change_mailbox(m);
		//	if(data!=NULL && len >0)
		//		flush_dcache_range((unsigned long)data,(unsigned long)data+len);
			MAIBOX2_IRQ_ENABLE(num);
			DSP_TRIGGER_IRQ(num);
			res=0;
		}
	local_irq_restore(flags);
	return res;
}


int get_mailbox_data(struct audiodsp_priv *priv,int num,struct mail_msg *msg)
{
	unsigned long flags;
	struct mail_msg *m;
	if(num>31 || num <0)
			return -1;
	local_irq_save(flags);
	m=&priv->mailbox_reg[num];
	pre_read_mailbox(m);
	msg->cmd=m->cmd; 
	msg->data=m->data;
    msg->data = (char *)((unsigned)msg->data+AUDIO_DSP_START_ADDR);
	msg->status=m->status;
	msg->len=m->len;
	m->status=0;
	after_change_mailbox(m);
	local_irq_restore(flags);
	return 0;
}



static irqreturn_t audiodsp_mailbox_irq(int irq, void *data)
{
	struct audiodsp_priv *priv=(struct audiodsp_priv *)data;
	unsigned long status,fiq_mask;
	struct mail_msg msg;
	status=READ_MPEG_REG(ASSIST_MBOX1_IRQ_REG); 
	fiq_mask=READ_MPEG_REG(ASSIST_MBOX1_FIQ_SEL); 
	status=status&fiq_mask;
	if(status&(1<<M1B_IRQ0_PRINT))
		{
		get_mailbox_data(priv,M1B_IRQ0_PRINT,&msg);
		SYS_CLEAR_IRQ(M1B_IRQ0_PRINT);
	//	inv_dcache_range((unsigned  long )msg.data,(unsigned long)msg.data+msg.len);
		printk(KERN_INFO "%s",msg.data);
		}
	if(status&(1<<M1B_IRQ1_BUF_OVERFLOW))
		{
		SYS_CLEAR_IRQ(M1B_IRQ1_BUF_OVERFLOW);
		DSP_PRNT("DSP BUF over flow\n");
		}
	if(status&(1<<M1B_IRQ2_BUF_UNDERFLOW))
		{
		SYS_CLEAR_IRQ(M1B_IRQ2_BUF_UNDERFLOW);
		DSP_PRNT("DSP BUF over flow\n");
		}
	if(status&(1<<M1B_IRQ3_DECODE_ERROR))
		{
		SYS_CLEAR_IRQ(M1B_IRQ3_DECODE_ERROR);
		priv->decode_error_count++;
		}
	if(status&(1<<M1B_IRQ4_DECODE_FINISH_FRAME))
		{
		struct frame_info *info;
		SYS_CLEAR_IRQ(M1B_IRQ4_DECODE_FINISH_FRAME);
		get_mailbox_data(priv,M1B_IRQ4_DECODE_FINISH_FRAME,&msg);
		info=(struct frame_info *)msg.data;
		if(info!=NULL)
			{
			priv->cur_frame_info.offset=info->offset;
			priv->cur_frame_info.buffered_len=info->buffered_len;
			}
		complete(&priv->decode_completion);
		}
	if(status& (1<<M1B_IRQ5_STREAM_FMT_CHANGED))
		{
		struct frame_fmt *fmt;
		SYS_CLEAR_IRQ(M1B_IRQ5_STREAM_FMT_CHANGED);
		get_mailbox_data(priv,M1B_IRQ5_STREAM_FMT_CHANGED,&msg);
		fmt=(void *)msg.data;
		//DSP_PRNT("frame format changed");
		if(fmt==NULL || (sizeof(struct frame_fmt )<msg.len))
			{
			DSP_PRNT("frame format message error\n");
			}
		else
			{
			if(fmt->valid&SUB_FMT_VALID)
				{
				priv->frame_format.sub_fmt=fmt->sub_fmt;
				priv->frame_format.valid|=SUB_FMT_VALID;
				}
			if(fmt->valid&CHANNEL_VALID)
				{
				priv->frame_format.channel_num=fmt->channel_num;
				priv->frame_format.valid|=CHANNEL_VALID;
				}
			if(fmt->valid&SAMPLE_RATE_VALID)
				{
				priv->frame_format.sample_rate=fmt->sample_rate;
				priv->frame_format.valid|=SAMPLE_RATE_VALID;
				}
			if(fmt->valid&DATA_WIDTH_VALID)
				{
				priv->frame_format.data_width=fmt->data_width;
				priv->frame_format.valid|=DATA_WIDTH_VALID;
				}
			}
		}
    	if(status& (1<<M1B_IRQ5_STREAM_RD_WD_TEST)){
            DSP_WD((0x84100000-4096+20*20),0);
    		SYS_CLEAR_IRQ(M1B_IRQ5_STREAM_RD_WD_TEST);
    		get_mailbox_data(priv,M1B_IRQ5_STREAM_RD_WD_TEST,&msg);
            int i;
            for(i = 0;i<12;i++){
                if((DSP_RD((0x84100000-512*1024+i*20)))!= (0xff00|i)){
                    DSP_PRNT("a9 read dsp reg error ,now 0x%x, should be 0x%x \n",(DSP_RD((0x84100000-512*1024+i*20))),12-i);
                }
               // DSP_PRNT("A9 audio dsp reg%d value 0x%x\n",i,DSP_RD((0x84100000-4096+i*20)));
            }
            for(i = 0;i<12;i++){
                DSP_WD((0x84100000-512*1024+i*20),(i%2)?i:(0xf0|i));
               
            }
            DSP_WD((0x84100000-512*1024+20*20),DSP_STATUS_HALT);
        //    DSP_PRNT("A9 mail box handle finished\n");
           // dsp_mailbox_send(priv, 1, M1B_IRQ5_STREAM_RD_WD_TEST, 0, NULL,0);
            
            
    		
        }

	return 0;
}

int audiodsp_init_mailbox(struct audiodsp_priv *priv)
{
	request_irq(INT_MAILBOX_1B, audiodsp_mailbox_irq,
                    IRQF_SHARED, "audiodsp_mailbox", (void *)priv);
	//WRITE_MPEG_REG(ASSIST_MBOX0_MASK, 0xffffffff);
	priv->mailbox_reg=(struct mail_msg *)MAILBOX1_REG(0);
	priv->mailbox_reg2=(struct mail_msg *)MAILBOX2_REG(0);
	return 0;
}
int audiodsp_release_mailbox(struct audiodsp_priv *priv)
{
	free_irq(INT_MAILBOX_1B,(void *)priv);
    return 0;
}




