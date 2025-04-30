#ifndef USB_TO_I2S_DRV_H
#define USB_TO_I2S_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "usb_to_i2s_types.h"

// #define USB_TO_I2S_PERIOD_US 1
//
// #define FRAME_SIZE_BYTES ((CONFIG_I2S_LRCK_FREQ_HZ / 1000 * 10) * CONFIG_I2S_CH_NUM * CONFIG_AUDIO_BIT_DEPTH_OCTETS)
// #define BLOCK_SIZE_BYTES (FRAME_SIZE_BYTES / CONFIG_FIFO_FRAME_SPLIT_NUM)
// #define BLOCK_SIZE_BYTES (FRAME_SIZE_BYTES / CONFIG_FIFO_FRAME_SPLIT_NUM)
//
// #define FIFO_RX_BLOCK_COUNT (CONFIG_FIFO_FRAME_SPLIT_NUM * CONFIG_FIFO_RX_FRAME_COUNT)
// #define FIFO_TX_BLOCK_COUNT (CONFIG_FIFO_FRAME_SPLIT_NUM * CONFIG_FIFO_TX_FRAME_COUNT)

bool usb_to_i2s_proc(void);
bool usb_to_i2s_init(void);
bool usb_to_i2s_stop(void);

#endif /* USB_TO_I2S_DRV_H  */
