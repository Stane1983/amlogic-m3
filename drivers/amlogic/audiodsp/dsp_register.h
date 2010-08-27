/*
dsp_register.h
*/
#ifndef DSP_REGISTER_H
#define DSP_REGISTER_H

#define SYS_MEM_START	0x80000000
#define SYS_MEM_SIZE	0x8000000

#define S_1K					(1024)
#define S_1M					(S_1K*S_1K)

#define AUDIO_DSP_MEM_SIZE		 S_1M
#define AUDIO_DSP_START_ADDR	0x84000000//((SYS_MEM_START+SYS_MEM_SIZE)-AUDIO_DSP_MEM_SIZE)
#define AUDIO_DSP_END_ADDR		((AUDIO_DSP_START_ADDR+AUDIO_DSP_MEM_SIZE))
#define REG_MEM_SIZE					(S_1K*4)




#define DSP_REG_OFFSET	(AUDIO_DSP_START_ADDR+ AUDIO_DSP_MEM_SIZE-REG_MEM_SIZE)
#define DSP_REG_END			(AUDIO_DSP_START_ADDR+ AUDIO_DSP_MEM_SIZE-4)
#define DSP_REG(x)			(DSP_REG_OFFSET | ((x)<<5))

#define DSP_STATUS				DSP_REG(0)
#define DSP_STATUS_HALT		('H'<<24 | 'a'<<16|'l'<<8 |'t')
#define DSP_STATUS_RUNING		('R'<<16|'u'<<8 |'n')
#define DSP_JIFFIES				DSP_REG(1)
#define DSP_STATUS_SLEEP  ('S'<<24 | 'L'<<16|'A'<<8 |'P')
#define DSP_STATUS_WAKEUP  ('W'<<24 | 'A'<<16|'K'<<8 |'E')

#define DSP_STACK_START   DSP_REG(3)
#define DSP_STACK_END   	DSP_REG(4)
#define DSP_GP_STACK_START   DSP_REG(5)
#define DSP_GP_STACK_END   	DSP_REG(6)

#define DSP_MEM_START  		DSP_REG(7)
#define DSP_MEM_END 	 		DSP_REG(8)


#define DSP_DECODE_OUT_START_ADDR  	DSP_REG(9)
#define DSP_DECODE_OUT_END_ADDR   	DSP_REG(10)
#define DSP_DECODE_OUT_RD_ADDR  	  DSP_REG(11)
#define DSP_DECODE_OUT_WD_ADDR  		DSP_REG(12)
		
#define MAILBOX1_REG(n)	DSP_REG(40+n)
#define MAILBOX2_REG(n)	DSP_REG(40+32+n)


#ifndef __ASSEMBLY__
/*mailbox struct*/
struct mail_msg{
int cmd;
int status;//0x1:pending.0:free
char *data;
int len;
};
#endif

#define M1B_IRQ0_PRINT							(0+16)
#define M1B_IRQ1_BUF_OVERFLOW					(1+16)
#define M1B_IRQ2_BUF_UNDERFLOW				(2+16)
#define M1B_IRQ3_DECODE_ERROR					(3+16)
#define M1B_IRQ4_DECODE_FINISH_FRAME 		(4+16)
#define M1B_IRQ5_STREAM_FMT_CHANGED 			(5+16)
#define M1B_IRQ5_STREAM_RD_WD_TEST 			(6+16)

#define M2B_IRQ0_DSP_HALT							(0)
#define M2B_IRQ1_DSP_RESET						(1)
#define M2B_IRQ2_DECODE_START					(2)
#define M2B_IRQ3_DECODE_STOP					(3)
#define M2B_IRQ4_AUDIO_INFO					(4)
#define M2B_IRQ0_DSP_SLEEP					(5)
#define M2B_IRQ0_DSP_WAKEUP					(6)

#define CMD_PRINT_LOG					(1234<<8 |1)

#define MDEC_TRIGGER_IRQ(irq)	{SET_MPEG_REG_MASK(ASSIST_MBOX0_FIQ_SEL,1<<irq);\
								WRITE_MPEG_REG(ASSIST_MBOX0_IRQ_REG,1<<irq);}
#define SYS_TRIGGER_IRQ(irq)		{SET_MPEG_REG_MASK(ASSIST_MBOX1_FIQ_SEL,1<<irq); \
								WRITE_MPEG_REG(ASSIST_MBOX1_IRQ_REG,1<<irq);}
#define DSP_TRIGGER_IRQ(irq)		{SET_MPEG_REG_MASK(ASSIST_MBOX2_FIQ_SEL,1<<irq); \
								WRITE_MPEG_REG(ASSIST_MBOX2_IRQ_REG,1<<irq);}

#define MDEC_CLEAR_IRQ(irq)		{CLEAR_MPEG_REG_MASK(ASSIST_MBOX0_FIQ_SEL,1<<irq); \
								WRITE_MPEG_REG(ASSIST_MBOX0_CLR_REG,1<<irq);}

#define SYS_CLEAR_IRQ(irq)		{CLEAR_MPEG_REG_MASK(ASSIST_MBOX1_FIQ_SEL,1<<irq); \
								WRITE_MPEG_REG(ASSIST_MBOX1_CLR_REG,1<<irq);}

#define DSP_CLEAR_IRQ(irq)		{CLEAR_MPEG_REG_MASK(ASSIST_MBOX2_FIQ_SEL,1<<irq); \
								WRITE_MPEG_REG(ASSIST_MBOX2_CLR_REG,1<<irq);}


#define MAIBOX0_IRQ_ENABLE(irq)		SET_MPEG_REG_MASK(ASSIST_MBOX0_MASK,1<<irq)
#define MAIBOX1_IRQ_ENABLE(irq)		SET_MPEG_REG_MASK(ASSIST_MBOX1_MASK,1<<irq)
#define MAIBOX2_IRQ_ENABLE(irq)		SET_MPEG_REG_MASK(ASSIST_MBOX2_MASK,1<<irq)
#endif


