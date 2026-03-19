#ifndef USB_SERIAL_TYPES_H
#define USB_SERIAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "usb_serial_const.h"

#define USB_SERIAL_VARIABLE                       \
    uint8_t TxBuff[USB_SERIAL_TX_SIZE_MAX];       \
    uint32_t tx_start_ms;                         \
    uint32_t rx_len;                              \
    bool tx_in_progress;                          \
    FifoChar_t TxFifo;                            \
    uint8_t RxData[USB_SERIAL_RX_SIZE_MAX];


#ifdef __cplusplus
}
#endif

#endif /* USB_SERIAL_TYPES_H */




