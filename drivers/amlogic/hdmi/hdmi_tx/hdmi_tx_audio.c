#include <linux/version.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/major.h>
#include <linux/platform_device.h>
#include <linux/mutex.h>
#include <linux/cdev.h>
#include "hdmi_tx_module.h"
#include "hdmi_info_global.h"

#undef PCM_USE_INFOFRAME

static const unsigned char channel_status_freq[]=
{
    0x0,
    0x3, //32K
    0x0, //44.1k
    0x2, //48k
    0x8, //88.2k
    0xa, //96k
    0xc, //176.4k
    0xe, //192k    
};    

static const unsigned char channel_status_sample_word_length[]=
{
    0x0,
    0x2, //16 bits
    0x3, //20 bits
    0xb //24 bits
};    

void hdmi_tx_set_N_CTS(unsigned N_value, unsigned CTS)
{
}

static void hdmi_tx_construct_aud_packet(Hdmi_tx_audio_para_t* audio_param, char* AUD_DB, unsigned char* CHAN_STAT_BUF)
{
#ifndef PCM_USE_INFOFRAME
    if((audio_param->type == CT_PCM)&&(audio_param->channel_num==CC_2CH)){
        if(AUD_DB){
            AUD_DB[0] = (audio_param->type<<4)|(CC_REFER_TO_STREAM) ; 
            AUD_DB[1] = (FS_REFER_TO_STREAM<<2)|SS_REFER_TO_STREAM;
            AUD_DB[4] = 0; //CA, 2 channel
            AUD_DB[5] = 0;//DM_INH<<7|LSV<<3
        }
        if(CHAN_STAT_BUF){
            CHAN_STAT_BUF[2]=0x10|(audio_param->channel_num+1);  CHAN_STAT_BUF[24+2]=0x20|(audio_param->channel_num+1); 
            CHAN_STAT_BUF[3]=CHAN_STAT_BUF[24+3]=channel_status_freq[audio_param->sample_rate];
            CHAN_STAT_BUF[4]=CHAN_STAT_BUF[24+4]=channel_status_sample_word_length[audio_param->sample_size]|
                    ((~channel_status_freq[audio_param->sample_rate])<<4);
        }            
    }
    else
#endif        
    {
        if(AUD_DB){
            AUD_DB[0] = (audio_param->type<<4)|audio_param->channel_num ; 
            AUD_DB[1] = (audio_param->sample_rate<<2)|audio_param->sample_size;
            AUD_DB[4] = 0; //CA, 2 channel
            AUD_DB[5] = 0;//DM_INH<<7|LSV<<3
        }
        if(CHAN_STAT_BUF){
            CHAN_STAT_BUF[3]=CHAN_STAT_BUF[24+3]=channel_status_freq[audio_param->sample_rate];
        }
    }
}

int hdmitx_set_audio(hdmitx_dev_t* hdmitx_device, Hdmi_tx_audio_para_t* audio_param)
{
    int i,ret=-1;
    unsigned char AUD_DB[32];
    unsigned char CHAN_STAT_BUF[24*2];
    for(i=0;i<32;i++) AUD_DB[i]=0;
    for(i=0;i<(24*2);i++) CHAN_STAT_BUF[i]=0;
    if(hdmitx_device->HWOp.SetAudMode(hdmitx_device, audio_param)>=0){
        hdmi_tx_construct_aud_packet(audio_param, AUD_DB, CHAN_STAT_BUF);
    
        hdmitx_device->HWOp.SetAudioInfoFrame(AUD_DB, CHAN_STAT_BUF);
        ret = 0;
    }
    return ret;
}



