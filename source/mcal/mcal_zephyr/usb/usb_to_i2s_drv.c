#include "usb_to_i2s_drv.h"

#include <stdint.h>
#include <string.h>
#include <zephyr/kernel.h>

#include "audio_types.h"
#include "audio_usb.h"
#include "audio_usb_config.h"
#include "data_fifo.h"
#include "gpio_drv.h"
#include "led_drv.h"
#include "log.h"
#include "utils_math.h"

#ifdef HAS_I2S
#include "i2s_drv.h"
#endif

DATA_FIFO_DEFINE(fifo_tx, FIFO_TX_BLOCK_COUNT, WB_UP(BLOCK_SIZE_BYTES));
DATA_FIFO_DEFINE(fifo_rx, FIFO_RX_BLOCK_COUNT, WB_UP(BLOCK_SIZE_BYTES));

/*4-overrun 9*/
//#define I2S_PCM_SAMPLE_CNT  (256) /*good*/
#define I2S_PCM_SAMPLE_CNT (480) /*good*/
#define I2S_PCM_FRAME_CNT (I2S_PCM_SAMPLE_CNT * 2)
static int32_t PcmToI2s[2][I2S_PCM_FRAME_CNT];

static char pcm_raw_data[FRAME_SIZE_BYTES];
static size_t pcm_block_size_total = 0;

#define MIN_I2S_CUNK_BYTE (2 * 2 * I2S_PCM_SAMPLE_CNT)
static uint32_t cur_sample = 0;
static I2s16BitSample_t I2sSample16bit;
static I2s32BitSample_t I2sSample32bit;
void* tmp_pcm_raw_data[CONFIG_FIFO_FRAME_SPLIT_NUM];

bool usb_to_i2s_proc(void) {
    I2sHandle_t* I2sNode = I2sGetNode(0);
    bool res = false;
    size_t pcm_block_size = 0;
    int ret = 0;
    AudioUsbInstance.spin++;
    uint32_t i = 0;
    for(i = 0; i < CONFIG_FIFO_FRAME_SPLIT_NUM; i++) {
        ret = data_fifo_pointer_last_filled_get(&fifo_rx, &tmp_pcm_raw_data[i], &pcm_block_size, K_FOREVER);
        if(0 == ret) {
            LOG_DEBUG(USB_TO_I2S, "GetPcmBlock %u byte", pcm_block_size);
            memcpy(pcm_raw_data + (i * BLOCK_SIZE_BYTES), tmp_pcm_raw_data[i], pcm_block_size);
            AudioUsbInstance.fifo_rx_byte_cnt += pcm_block_size;
            pcm_block_size_total += pcm_block_size;
            ret = data_fifo_block_free(&fifo_rx, &tmp_pcm_raw_data[i]);
            if(0 == res) {
                res = true;
            } else {
                res = false;
            }
        } else {
            res = false;
        }
    }


    for(i = 0; i < (FRAME_SIZE_BYTES); i += 4) {
        if(I2S_PCM_SAMPLE_CNT <= cur_sample) {
            cur_sample = 0;
            gpio_toggle(LedConfig[0].pad.byte);
        }
        memcpy(I2sSample16bit.data, &pcm_raw_data[i], 4);
#if 0
            I2sSample16bit.u_right=reverse_byte_order_uint16(I2sSample16bit.u_right);
            I2sSample16bit.u_left=reverse_byte_order_uint16(I2sSample16bit.u_left);
#endif
        I2sSample32bit.left = ((int32_t)I2sSample16bit.left) << 10;
        I2sSample32bit.right = ((int32_t)I2sSample16bit.right) << 10;
#if 0
            I2sSample32bit.u_right=reverse_byte_order_uint32(I2sSample32bit.u_right);
            I2sSample32bit.u_left=reverse_byte_order_uint32(I2sSample32bit.u_left);
#endif
        // memcpy(&PcmToI2s[I2sNode->prev_tx_track][cur_sample*2], I2sSample32bit.data, 8);
        memcpy(&PcmToI2s[I2sNode->cur_tx_track][cur_sample * 2], I2sSample32bit.data, 8);
        cur_sample++;
    }
    return res;
}

bool usb_to_i2s_init(void) {
    bool res = false;
    LOG_INFO(USB_TO_I2S, "AudioCardInit..");
    LOG_INFO(USB_TO_I2S, "I2S_PCM_SAMPLE_CNT %u", I2S_PCM_SAMPLE_CNT);
    LOG_INFO(USB_TO_I2S, "BLOCK_SIZE_BYTES %u", BLOCK_SIZE_BYTES);
    LOG_INFO(USB_TO_I2S, "FRAME_SIZE_BYTES %u", FRAME_SIZE_BYTES);
    LOG_INFO(USB_TO_I2S, "I2S_LRCK_FREQ %u Hz", CONFIG_I2S_LRCK_FREQ_HZ);
    LOG_INFO(USB_TO_I2S, "FIFO_FRAME_SPLIT_NUM %u", CONFIG_FIFO_FRAME_SPLIT_NUM);
    LOG_INFO(USB_TO_I2S, "AUDIO_BIT_DEPTH %u byte", CONFIG_AUDIO_BIT_DEPTH_OCTETS);
    LOG_INFO(USB_TO_I2S, "I2S_CH_NUM %u ", CONFIG_I2S_CH_NUM);
    int ret = 0;
    memset(&PcmToI2s[0][0], 0, sizeof(PcmToI2s));
    cur_sample = 0;
    AudioUsbInstance.spin=0;
    if(!fifo_tx.initialized) {
        ret = data_fifo_init(&fifo_tx);
        if(0 == ret) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(USB_TO_I2S, "Failed to set up tx FIFO");
        }
    }

    if(!fifo_rx.initialized) {
        ret = data_fifo_init(&fifo_rx);
        if(0 == ret) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(USB_TO_I2S, "Failed to set up rx FIFO");
        }
    }

    ret = audio_usb_start(&fifo_tx, &fifo_rx);
    if(0 == ret) {
        res = true;
    } else {
        res = false;
        LOG_ERROR(USB_TO_I2S, "UsbStartErr");
    }

#ifdef HAS_I2S
    res = i2s_set_join_write(0, (uint32_t*)&PcmToI2s[0][0], (uint32_t*)&PcmToI2s[1][0]);
    if(false == res) {
        LOG_ERROR(USB_TO_I2S, "JoinErr");
    }
    I2sHandle_t* I2sNode = I2sGetNode(0);
    if(I2sNode) {
        i2s_dma_stop(0);
        I2sNode->in_progress = false;
        I2sNode->stop_needed = false;
        I2sNode->switch_needed = true;
        LOG_DEBUG(USB_TO_I2S, "StartI2S");
        res = i2s_api_write(0, (uint32_t*)&PcmToI2s[0][0], I2S_PCM_FRAME_CNT);
        if(false == res) {
            AudioUsbInstance.i2s_tx_err++;
        } else {
            LOG_DEBUG(USB_TO_I2S, "StartI2SOk");
        }
    }
#endif
    return res;
}

bool usb_to_i2s_stop(void) {
    bool res = true;
    LOG_WARNING(USB_TO_I2S, "stop");
    audio_usb_stop();
    data_fifo_empty(&fifo_rx);
    data_fifo_empty(&fifo_tx);
    return res;
}
