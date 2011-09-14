/*
 *
 * arch/arm/mach-meson/bcm-bt.c
 *
 *  Copyright (C) 2010 AMLOGIC, INC.
 *
 * License terms: GNU General Public License (GPL) version 2
 * Platform machine definition.
 */
 
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/rfkill.h>
#include <linux/bt-device.h>

#include <net/bluetooth/bluetooth.h>                                                                                  
#include <net/bluetooth/hci_core.h>

extern struct bt_dev_data bt_dev;
void rfkill_switch_all(enum rfkill_type type, bool blocked);

static unsigned long bt_baud;
extern int get_baud(int line);                                                                                        
extern void set_baud(int line, unsigned long newbaud);

static int bt_set_block(void *data, bool blocked)
{
    pr_info("BT_RADIO going: %s\n", blocked ? "off" : "on");

	if (!blocked) {
		pr_info("BCM_BT: going ON\n");
        if (NULL != bt_dev.bt_dev_on) {
		    bt_dev.bt_dev_on();
        }
	} else {
		pr_info("BCM_BT: going OFF\n");
        if (NULL != bt_dev.bt_dev_off) {
		    bt_dev.bt_dev_off();
        }
	}
    return 0;
}

static const struct rfkill_ops bt_rfkill_ops = {
	.set_block = bt_set_block,
};

static int bt_suspend(struct platform_device *pdev, pm_message_t state)                                               
{
    struct hci_dev *hdev;
    //unsigned char buf[10] = {0x01, 0x0a, 0x0a, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00};
    //u16 opcode = (u16)((0x27 & 0x03ff)|(0x3f << 10));
    
    pr_info("BCM_BT: going suspend\n");

    if( hdev = hci_dev_get(0)){
        //hci_send_cmd(hdev, opcode, 10, buf);
        //hci_suspend_dev(hdev);

        //if (NULL != bt_dev.bt_dev_suspend) {
        //    bt_dev.bt_dev_suspend();
        //}
        //msleep(10);
        bt_baud = get_baud(1);
    }

    return 0;
}

static int bt_resume(struct platform_device *pdev)
{
    struct hci_dev *hdev;
    
    pr_info("BCM_BT: going resume\n");

    if( hdev = hci_dev_get(0)){
        //hci_resume_dev(hdev);
        //if (NULL != bt_dev.bt_dev_resume) {
            //bt_dev.bt_dev_resume();
        //}
        set_baud(1, bt_baud);
    }

    return 0;
}

static int __init bt_probe(struct platform_device *pdev)
{
	int rc = 0;
	struct rfkill *bt_rfk;

    /* default to bluetooth off */
    //rfkill_switch_all(RFKILL_TYPE_BLUETOOTH, 1);
    if (NULL != bt_dev.bt_dev_off) {
        bt_dev.bt_dev_off();
    }
    
	bt_rfk = rfkill_alloc("bt-dev", &pdev->dev, RFKILL_TYPE_BLUETOOTH,
			&bt_rfkill_ops, NULL);
						   
	if (!bt_rfk) {
        printk("rfk alloc fail\n");
		rc = -ENOMEM;
		goto err_rfk_alloc;
	}
    rfkill_init_sw_state(bt_rfk, false);
	rc = rfkill_register(bt_rfk);
	if (rc){
        printk("rfkill_register fail\n");
		goto err_rfkill;
    }
	platform_set_drvdata(pdev, bt_rfk);

	return 0;	
	
err_rfkill:
	rfkill_destroy(bt_rfk);
err_rfk_alloc:
	return rc;
	
}

static int bt_remove(struct platform_device *pdev)
{
	struct rfkill *rfk = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);

	if (rfk) {
		rfkill_unregister(rfk);
		rfkill_destroy(rfk);
	}
	rfk = NULL;

	return 0;
}
static struct platform_driver bt_driver = {
	.driver		= {
		.name	= "bt-dev",
	},
	.probe		= bt_probe,
	.remove		= bt_remove,
	.suspend    = bt_suspend,
    .resume     = bt_resume,
};

static int __init bt_init(void)
{
    printk("amlogic rfkill init\n");
    if (NULL != bt_dev.bt_dev_init) {
		    bt_dev.bt_dev_init();
        }
	return platform_driver_register(&bt_driver);
}
static void __exit bt_exit(void)
{
	platform_driver_unregister(&bt_driver);
}
module_init(bt_init);
module_exit(bt_exit);
MODULE_DESCRIPTION("bt rfkill");
MODULE_AUTHOR("");
MODULE_LICENSE("GPL");
