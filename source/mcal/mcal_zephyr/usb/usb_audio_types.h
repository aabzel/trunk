
#ifndef AUDIO_USB_TYPES_H
#define AUDIO_USB_TYPES_H

#include <stdint.h>
#include <stdbool.h>

#include "usb_audio_const.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

#ifndef HAS_AUDIO_USB
#error "+HAS_AUDIO_USB"
#endif

typedef struct {
    uint32_t rx_byte;
    uint32_t rx_cnt;
    uint32_t tx_cnt;
    uint32_t min_size;
    uint32_t max_size;
    uint32_t fifo_rx_byte_cnt;
    uint32_t err_cnt;
    uint32_t overrun_cnt;
    uint32_t i2s_tx_err;
    uint32_t spin;
    bool init;
}AudioUsb_t;

#endif /* AUDIO_USB_TYPES_H */
