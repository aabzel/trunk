#ifndef USB_SERIAL_H
#define USB_SERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "usb_serial_types.h"

bool usb_serial_init_one(uint8_t num);
bool usb_serial_send(uint8_t num, const uint8_t* const Buf, const uint16_t size);
bool usb_serial_proc_one(const uint8_t num);

bool usb_serial_tx_next(const uint8_t num) ;
bool usb_serial_writer_transmit(void* base);
void usb_serial_putc(void* stream_ptr, char ch);
void usb_serial_puts(void* stream_ptr, const char* str, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* USB_SERIAL_H */




