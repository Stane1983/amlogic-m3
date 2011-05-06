/*
 *
 * arch/arm/mach-meson/usbclock.c
 *
 *  Copyright (C) 2010 AMLOGIC, INC.
 *
 * License terms: GNU General Public License (GPL) version 2
 * Platform machine definition.
 */
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/dma-mapping.h>
#include <mach/hardware.h>
#include <mach/platform.h>
#include <mach/memory.h>
#include <asm/mach-types.h>
#include <asm/mach/arch.h>
#include <mach/lm.h>


static const char * clock_src_name[]={
		"XTAL input",
		"XTAL input divided by 2",
		"other PLL",
		"DDR PLL",
		"dmod PLL"
};
int set_usb_phy_clk(int rate)
{

//    int divider =0;
    int clk_sel = rate;
    int i;
    int time_dly = 50000;


	// ------------------------------------------------------------
	//  CLK_SEL: These bits select the source for the 12Mhz: 
	// 0 = XTAL input (24, 25, 27Mhz)
	// 1 = XTAL input divided by 2
	// 2 = other PLL output
	// 3 = DDR pll clock (typically 400mhz)
	// 4 = demod 240Mhz PLL output
	CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_CLK_SEL);
	//clk_sel = 0; // 24M CLK 
	//clk_sel = 1; // 12M, Phy default setting is 12Mhz
	//clk_sel = 2; // other PLL, 540M
	//clk_sel = 3; // DDR, 369M
	//clk_sel = 4; // demod, 240M
	
	printk(KERN_NOTICE"USB PHY clock souce: %s\n",clock_src_name[clk_sel]);
	SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (clk_sel<<5 ));

	CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG,PREI_USB_PHY_CLK_DIV);
	switch(clk_sel)
	{
		case USB_PHY_CLOCK_SEL_XTAL:
			//XTAL 24M, Divide by 2
			SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (1 << 24));
			break;
			
		case USB_PHY_CLOCK_SEL_XTAL_DIV2:
			//XTAL 24M, Divide by 1
			SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (0 << 24));
			break;
			
		case USB_PHY_CLOCK_SEL_OTHER_PLL:
			//Other PLL running at 540M (540/(44+1)=12)
			SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (44 << 24));
			break;
			
		case USB_PHY_CLOCK_SEL_DDR_PLL:
			//DDR runing 396MHz (396/(32+1)=12)
			SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (32 << 24));
			break;
			
		case USB_PHY_CLOCK_SEL_DEMOD_PLL:
			// demod 240M (240/(19+1) = 12)
			SET_CBUS_REG_MASK(PREI_USB_PHY_REG, (19 << 24));
			break;
	}

	// Open clock gate, to enable CLOCK to usb phy 
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_CLK_GATE);
    i=0;
    while(i++<time_dly){};
	
    /*  Reset USB PHY A  */
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_AHB_RSET);
    i=0;
    while(i++<time_dly){};  
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_AHB_RSET);
    i=0;
    while(i++<time_dly){};
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_CLK_RSET);
    i=0;
    while(i++<time_dly){};      
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_CLK_RSET);
    i=0;
    while(i++<time_dly){};
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_PLL_RSET);
    i=0;
    while(i++<time_dly){};
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_PLL_RSET);
    i=0;
    while(i++<time_dly){};

    // ------------------------------------------------------------ 
    // Reset the PHY A by setting POR high for 10uS.
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_POR);
    i=0;
    while(i++<time_dly){};
    // Set POR to the PHY high

    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_A_POR);
    i=0;
    while(i++<time_dly){};
    
    /* Reset USB PHY B */
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_AHB_RSET);
    i=0;
    while(i++<time_dly){};
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_AHB_RSET);
    i=0;
    while(i++<time_dly){};
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_CLK_RSET);
    i=0;
    while(i++<time_dly){};
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_CLK_RSET);
    i=0;
    while(i++<time_dly){};
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_PLL_RSET);
    i=0;
    while(i++<time_dly){};
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_PLL_RSET);
    i=0;
    while(i++<time_dly){};

    // ------------------------------------------------------------ 
    // Reset the PHY B by setting POR high for 10uS.
    SET_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_POR);
    i=0;
    while(i++<time_dly){};

    // Set POR to the PHY high
    CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, PREI_USB_PHY_B_POR);
    i=0;
    while(i++<time_dly){};

    return 0;
}

EXPORT_SYMBOL(set_usb_phy_clk);


/*
 * Don't call this function when usb device is operating.
 */
void set_usb_ctl_por(int index,int is_power_on)
{

    int msk = PREI_USB_PHY_A_POR;
    char * msg;
	
    if(index == 1)
        msk = PREI_USB_PHY_B_POR;

    if (is_power_on){
        msg = "on";
        CLEAR_CBUS_REG_MASK(PREI_USB_PHY_REG, msk);
    }
    else{
        msg = "off";
        SET_CBUS_REG_MASK(PREI_USB_PHY_REG, msk);
    }
    printk(KERN_INFO "usb %c %s\n",(index?'B':'A'),msg);

}
EXPORT_SYMBOL(set_usb_ctl_por);