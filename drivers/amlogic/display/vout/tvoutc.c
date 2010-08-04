/*
 * Amlogic Apollo
 * frame buffer driver
 *
 * Copyright (C) 2009 Amlogic, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the named License,
 * or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Author:  Tim Yao <timyao@amlogic.com>
 *
 */

#include <linux/errno.h>
#include <linux/kernel.h>

#include <mach/am_regs.h>

#include <linux/vout/vinfo.h>
#include "tvoutc.h"

#define CLOCK_SRC_AUDIOPLL
//#define CLOCK_SRC_VIDEOPLL

//#define CRYSTAL_25M
#define CRYSTAL_24M

#include "tvregs.h"

#define  SET_VDAC(index,val)   (WRITE_MPEG_REG((index+VENC_VDAC_DACSEL0),val))
static const unsigned int  signal_set[SIGNAL_SET_MAX][3]=
{
	{	VIDEO_SIGNAL_TYPE_INTERLACE_Y,     // component interlace
		VIDEO_SIGNAL_TYPE_INTERLACE_PB,
		VIDEO_SIGNAL_TYPE_INTERLACE_PR,
	},
	{
		VIDEO_SIGNAL_TYPE_CVBS,            	//cvbs&svideo
		VIDEO_SIGNAL_TYPE_SVIDEO_LUMA,    
    		VIDEO_SIGNAL_TYPE_SVIDEO_CHROMA,   
	},
	{	VIDEO_SIGNAL_TYPE_PROGRESSIVE_Y,     //progressive.
		VIDEO_SIGNAL_TYPE_PROGRESSIVE_PB,
		VIDEO_SIGNAL_TYPE_PROGRESSIVE_PR,
	},
};
static  const  char*   signal_table[]={
	"INTERLACE_Y ", /**< Interlace Y signal */
    	"CVBS",            /**< CVBS signal */
    	"SVIDEO_LUMA",     /**< S-Video luma signal */
    	"SVIDEO_CHROMA",   /**< S-Video chroma signal */
    	"INTERLACE_PB",    /**< Interlace Pb signal */
    	"INTERLACE_PR",    /**< Interlace Pr signal */
    	"INTERLACE_R",     /**< Interlace R signal */
         "INTERLACE_G",     /**< Interlace G signal */
         "INTERLACE_B",     /**< Interlace B signal */
         "PROGRESSIVE_Y",   /**< Progressive Y signal */
         "PROGRESSIVE_PB",  /**< Progressive Pb signal */
         "PROGRESSIVE_PR",  /**< Progressive Pr signal */
         "PROGEESSIVE_R",   /**< Progressive R signal */
         "PROGEESSIVE_G",   /**< Progressive G signal */
         "PROGEESSIVE_B",   /**< Progressive B signal */
		
	};
//120120
void  change_vdac_setting(unsigned int  vdec_setting,vmode_t  mode)
{
	unsigned  int  signal_set_index=0;
	unsigned int  idx=0,bit=5,i;
	switch(mode )
	{
		case VMODE_480I:
		case VMODE_576I:
		signal_set_index=0;
		bit=5;
		break;
		case VMODE_480CVBS:
		case VMODE_576CVBS:
		signal_set_index=1;	
		bit=2;
		break;
		default :
		signal_set_index=2;
		bit=5;
		break;
	}
	for(i=0;i<3;i++)
	{
		idx=vdec_setting>>(bit<<2)&0xf;
		printk("dac index:%d ,signal:%s\n",idx,signal_table[signal_set[signal_set_index][i]]);
		SET_VDAC(idx,signal_set[signal_set_index][i]);
		bit--;
	}
	
}
static void enable_vsync_interrupt(void)
{
	/* M1 chip test only, use audio PLL as video clock source */
	SET_CBUS_REG_MASK(HHI_MPEG_CLK_CNTL, 1<<11);
	
    if (READ_MPEG_REG(ENCP_VIDEO_EN) & 1) {
        WRITE_MPEG_REG(VENC_INTCTRL, 0x200);

        while ((READ_MPEG_REG(VENC_INTFLAG) & 0x200) == 0) {
            u32 line1, line2;

            line1 = line2 = READ_MPEG_REG(VENC_ENCP_LINE);

            while (line1 >= line2) {
                line2 = line1;
                line1 = READ_MPEG_REG(VENC_ENCP_LINE);
            }

            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            if (READ_MPEG_REG(VENC_INTFLAG) & 0x200) {
                break;
            }

            WRITE_MPEG_REG(ENCP_VIDEO_EN, 0);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);

            WRITE_MPEG_REG(ENCP_VIDEO_EN, 1);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
            READ_MPEG_REG(VENC_INTFLAG);
        }
    }
    else{
        WRITE_MPEG_REG(VENC_INTCTRL, 0x2);
    }
}

int tvoutc_setmode(tvmode_t mode)
{
    const  reg_t *s;

    if (mode >= TVMODE_MAX) {
        printk(KERN_ERR "Invalid video output modes.\n");
        return -ENODEV;
    }

    printk(KERN_DEBUG "TV mode %s selected.\n", tvinfoTab[mode].id);
   
    s = tvregsTab[mode];
			
    while (MREG_END_MARKER != s->reg)
        setreg(s++);

    enable_vsync_interrupt();
    
    WRITE_MPEG_REG(VPP_POSTBLEND_H_SIZE, tvinfoTab[mode].xres);

    return 0;
}
