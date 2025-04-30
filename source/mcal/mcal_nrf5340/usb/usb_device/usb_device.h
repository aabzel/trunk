#ifndef USB_DEVICE_H
#define USB_DEVICE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


#include "usb_device_types.h"

#ifndef HAS_USB_DEVICE
#error "Error +HAS_USB_DEVICE"
#endif

bool usb_device_proc(void);
bool usb_device_init(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_H */
