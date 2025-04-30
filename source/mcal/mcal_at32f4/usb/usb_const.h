#ifndef USB_CONST_H
#define USB_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "usb_const.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

typedef enum {
    USB_SPEED_FS=0,
    USB_SPEED_HS=1,
    USB_SPEED_UNDEF=2,
}UsbSpeed_t;

typedef enum {
    USB_DEVICE_SPEED_FS=0,
    USB_DEVICE_SPEED_HS=1,
    USB_DEVICE_SPEED_UNDEF=2,
}UsbDeviceSpeed_t;

typedef enum{
    USB_HOST_SPEED_HS=0,
    USB_HOST_SPEED_FS=1,
    USB_HOST_SPEED_UNDEF=2,
}UsbHostSpeed_t;

typedef enum{
    USB_ROLE_HOST=0,
    USB_ROLE_DEVICE=1,
    USB_ROLE_UNDEF=2,
}UsbRole_t;

#ifdef __cplusplus
}
#endif

#endif /* USB_CONST_H */

