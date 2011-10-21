/*
 * $Id: loopback.c 14480 2010-03-04 20:07:59Z phth $
 */

/*
 * Implements the loop back test for the sdio, spi and kspi transports.
 * This is for transport reliability verification and throughput assessment.
 */

/* This should not be compiled when USE_WIFI is not defined */
#ifndef USE_WIFI

#include <linux/file.h>
#include <linux/time.h>

/* Can be used to save firmware during firmware download, normally unused */
static int dump_bin_to_file(const char *fname, const void *data, size_t len)
{
   struct file *pf;
   int err;
   mm_segment_t save;

   pf = filp_open(fname, O_RDWR | O_CREAT, 0600);
   if ((!pf) || IS_ERR(pf) || (!pf->f_op)) {
      KDEBUG(ERROR, "filp_open('%s') failed", fname);
      return -1;
   }

   save = get_fs();
   set_fs(KERNEL_DS);
   err = (pf->f_op->write)(pf, data, len, &pf->f_pos);
   fput(pf);
   set_fs(save);
   if ((err < 0) || ((size_t) err != len)) return -1;
   
   return 0;
}

static int get_bin_from_file(const char *fname, void *data, size_t *len)
{
   struct file *pf;
   int err;
   mm_segment_t save;

   pf = filp_open(fname, O_RDONLY, 0600);
   if ((!pf) || IS_ERR(pf) || (!pf->f_op)) {
      KDEBUG(ERROR, "filp_open('%s') failed", fname);
      return -1;
   }

   save = get_fs();
   set_fs(KERNEL_DS);
   err = (pf->f_op->read)(pf, data, *len, &pf->f_pos);
   fput(pf);
   set_fs(save);

   if (err < 0)
      return -1;
   else {
      *len = (size_t) err;
      return 0;
   }
}

struct semaphore loopback_sema; /* balance between RX and TX path */

static int do_test(void* dummy)
{
   int i, j;
   int min_size = 1600; /* XMAC_MIN_SIZE; */
   int step_size = 0;
   int num_msg = 25000;
   int count;
   struct sk_buff *skb;
   unsigned char* fw_buf;
   size_t fw_len;
   unsigned int status;

   unsigned char hic_alignment_req[] = {
      0x1e, 0x00, 0x07, 0x03, 0x08, 0x00, 0x06, 0x00,
      0x01, 0x00, 0x00, 0x00, 0x20, 0x00, 0x08, 0x00,
      0x00, 0x10, 0x00, 0xff, 0xff, 0x06, 0x00, 0x00,
      0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
   };
   size_t hic_alignment_req_size =
         sizeof(hic_alignment_req) / sizeof(hic_alignment_req[0]);

#ifdef LOOPBACK_HIC_MIN_SIZE 
   /* Define the minimum size of the HIC messages generated by the target */ 
   hic_alignment_req[12] = (LOOPBACK_HIC_MIN_SIZE) & 0xff; 
   hic_alignment_req[13] = (LOOPBACK_HIC_MIN_SIZE >> 8) & 0xff; 
#endif 

#ifdef LOOPBACK_SIZE_ALIGN 
   /* Define the size of the HIC messages generated by the target 
      to be a multiple of LOOPBACK_SIZE_ALIGN */ 
   hic_alignment_req[14] = (LOOPBACK_HIC_MIN_SIZE) & 0xff; 
   hic_alignment_req[15] = (LOOPBACK_HIC_MIN_SIZE >> 8) & 0xff; 
#endif 

   /* Define how the target will generate IRQs */  
   hic_alignment_req[16] = LOOPBACK_HIC_CTRL_ALIGN_HATTN;
 
   GPIO_START_MEASURE();
   KDEBUG(TRANSPORT, "ENTER");
   sema_init(&loopback_sema, LOOPBACK_SEMA_INIT);
   msleep(500);

   status = -1;
   fw_len = 512 * 1024;
   fw_buf = kmalloc(fw_len, GFP_KERNEL);
   if (fw_buf) {
      status = get_bin_from_file("/etc/wifi/fw.bin", fw_buf, &fw_len);
      if (status == 0)
         status = LOOPBACK_FW_DOWNLOAD(fw_buf, fw_len, NULL);
      kfree(fw_buf);
   }
   if (status) {
      KDEBUG(ERROR, "Failed to load fw (err: %d)", status);
      goto exit;
   }

   printk("After fw download - status = 0\n");

   skb = dev_alloc_skb(hic_alignment_req_size);
   skb_put(skb, hic_alignment_req_size);
   memcpy(skb->data, hic_alignment_req, hic_alignment_req_size);
   LOOPBACK_SEND(skb);
   msleep(200);

   for (count = 0; count < num_msg; count++) {

      KDEBUG(TRANSPORT, "Loopback Pkt [%d]\n", count);
      i = min_size + (count * step_size) % MAX_PACKET_SIZE;

      skb = dev_alloc_skb(i + XMAC_ALIGNMENT);  
      TRSP_ASSERT(skb);
      if (!skb) {
         status = -ENOMEM;
         break;
      }

      skb_put(skb, i);
      ((uint16_t*) skb->data)[0] = i - 2;
      skb->data[2] = 0x3;
      skb->data[3] = 0x0;
      skb->data[4] = 0x10;
      
      for (j = 5; j < 16; j++)
         skb->data[j] = 0x0;

      for (j = 16; j < i; j++)
         skb->data[j] = j & 0xff;

      GPIO_STOP_MEASURE();
      status = down_interruptible(&loopback_sema);
      GPIO_START_MEASURE();
      TRSP_ASSERT(status == 0);
      if (status)
         break;
      LOOPBACK_SEND(skb);
   }
   msleep(100); /* wait for packets to be received before exiting */

exit:
   LOOPBACK_INTERRUPT(IRQ_OP_DISABLE);
   host_exit();
   LOOPBACK_SHUTDOWN_TARGET();

   KDEBUG(TRANSPORT, "EXIT");
   GPIO_STOP_MEASURE();
   return status;
}

static void do_test_rx(struct sk_buff *skb)
{
   int i;
   static int pkt_count = 0;
   static unsigned long jiffies_base, total_bytes = 0;
   extern struct semaphore loopback_sema;

   if ((pkt_count & 0x7f) == 0) {
      unsigned long msec = 0;
      unsigned long throughput = 0;

      if (pkt_count) {
         msec = jiffies_to_msecs(jiffies - jiffies_base);
         throughput = 2 * (8 * total_bytes) / msec;
      }
      else
         jiffies_base = jiffies;

      printk("RX: %d packets, %lu msec, %lu kbit/sec\n", pkt_count, msec, throughput);
   }

   if (pkt_count++ > 0) {
      up(&loopback_sema);
      total_bytes += skb->len;

      /* Perform test */
      for (i = 16; i < skb->len; ++i)
         if (skb->data[i] != (i & 0xff))
            break;

      if (i < skb->len) {
         printk("RX Pkt[%d] failed *********\n", pkt_count);
         nano_util_printbuf(skb->data, skb->len, "RX failed");
      }
   }

   dev_kfree_skb(skb);
}

void nano_util_printbuf(const void *data, size_t len, const char *prefix)
{
   int i, j;
   const unsigned char *p = data;

   for (i = 0; i < len; i += 16) {
      printk("%s %04x: ", prefix, i);
      for (j = 0; j < 16; j++) {
         if (i + j < len)
            printk("%02x ", p[i+j]);
         else
            printk("   ");
      }
      printk(" : ");
      for (j = 0; j < 16; j++) {
         if (i + j < len) {
#define isprint(c) ((c) >= 32 && (c) <= 126)
            if (isprint(p[i+j]))
               printk("%c", p[i+j]);
            else
               printk(".");
         } else
            printk(" ");
      }
      printk("\n");
   }
}

#endif
