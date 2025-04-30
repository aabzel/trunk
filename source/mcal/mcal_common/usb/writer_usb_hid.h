#ifndef SRC_USB_HID_WRITER_H
#define SRC_USB_HID_WRITER_H

#include <stdbool.h>

#include "writer_generic.h"

#define USB_HID_TX_ARRAY_SIZE 600U

#ifndef HAS_HID
#error "Add HAS_HID"
#endif

#ifndef HAS_USB_DEVICE
#error "Add HAS_USB_DEVICE"
#endif

extern generic_writer_t usb_hid_o;
#define DBG_USB_HID_STREAM (&usb_hid_o.s)

bool usb_hid_writer_init(void);
bool usb_hid_writer_transmit(struct generic_writer_s* s);

#endif /* SRC_USB_HID_WRITER_H */
