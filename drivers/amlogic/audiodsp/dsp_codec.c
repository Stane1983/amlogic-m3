#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/cache.h>
#include <asm/cacheflush.h>
//#include <asm/arch/am_regs.h>
#include <mach/am_regs.h>
//#include <asm/bsp.h>

#include <linux/amports/ptsserv.h>
//#include <asm/dsp/dsp_register.h>

#include "dsp_microcode.h"
#include "audiodsp_module.h"
#include "dsp_control.h"

#include "dsp_mailbox.h"

#include "dsp_codec.h"

 int dsp_codec_start( struct audiodsp_priv *priv)
 	{
 		return dsp_mailbox_send(priv,1,M2B_IRQ2_DECODE_START,0,0,0);
		 
 	}
  int dsp_codec_stop( struct audiodsp_priv *priv)
  	{
  		return dsp_mailbox_send(priv,1,M2B_IRQ3_DECODE_STOP,0,0,0);
  	}


  int dsp_codec_get_bufer_data_len(struct audiodsp_priv *priv)
{
#define REVERSD_BYTES	32
#define CACHE_ALIGNED(x)	(x&(~0x1f))
  		unsigned long rp,wp,len,flags;
		local_irq_save(flags);
  		rp=dsp_codec_get_rd_addr(priv);
		wp=dsp_codec_get_wd_addr(priv);
		if(rp>wp)
			len=priv->stream_buffer_size-(rp-wp);
		else
			len=(wp-rp);
		len=(len>REVERSD_BYTES)?(len-REVERSD_BYTES):0;
		len=CACHE_ALIGNED(len);
		local_irq_restore(flags);
		return len;
 }

unsigned long dsp_codec_inc_rd_addr(struct audiodsp_priv *priv,int size)
{
	unsigned long rd,flags;
	local_irq_save(flags);
	rd=dsp_codec_get_rd_addr(priv);
	rd=rd+size;
	if(rd>=priv->stream_buffer_end)
		rd=rd-priv->stream_buffer_size;
	DSP_WD(DSP_DECODE_OUT_RD_ADDR,rd);
	local_irq_restore(flags);
	return rd;
}

#define CONFIG_AM_PTSMGR
u32 dsp_codec_get_current_pts(struct audiodsp_priv *priv)
{
#ifdef CONFIG_AM_PTSMGR
	u32  pts;
       u32 delay_pts;
	int len;
	int frame_nums;
	int res;
	
	mutex_lock(&priv->stream_buffer_mutex);
	if(priv->stream_fmt == MCODEC_FMT_COOK)
		{
		pts = priv->cur_frame_info.offset;
		mutex_unlock(&priv->stream_buffer_mutex);
		}
	else
		{
#if 0
	res=pts_lookup_offset(PTS_TYPE_AUDIO,priv->cur_frame_info.offset,&pts,0);
	if(res==0)
		{
		priv->out_len_after_last_valid_pts=0;
		len=priv->cur_frame_info.buffered_len+dsp_codec_get_bufer_data_len(priv);
		frame_nums=(len*8/(priv->frame_format.data_width*priv->frame_format.channel_num));
		delay_pts=(frame_nums*90)/(priv->frame_format.sample_rate/1000);
		if(pts>delay_pts)
			pts-=delay_pts;
		else
			pts=0;
		priv->last_valid_pts=pts;
		}
#endif /* 0 */
	//else if(priv->last_valid_pts>0)
		{
		pts=priv->last_valid_pts;
		len=priv->out_len_after_last_valid_pts;
		frame_nums=(len*8/(priv->frame_format.data_width*priv->frame_format.channel_num));
		pts+=(frame_nums*90)/(priv->frame_format.sample_rate/1000);
		}
#if 0
	else
		{
		pts=-1;
		}
#endif /* 0 */
	mutex_unlock(&priv->stream_buffer_mutex);
		}
	return pts;
#endif	
	return -1;
}
 
  
