#ifndef USB_GENERAL_CONST_H
#define USB_GENERAL_CONST_H

#ifdef HAS_USB_CUSTOM
#include "usb_custom_const.h"
#endif

#include "usb_dep.h"

#define USB_VERSION "4"
#define USB_POLL_PERIOD_US 1

typedef enum {
    USB_MCAL_SPEED_FS = 1,
    USB_MCAL_SPEED_HS = 2,

    USB_MCAL_SPEED_UNDEF = 0,
}UsbSpeed_t;

typedef enum {
    USB_DEVICE_SPEED_FS = 1,
    USB_DEVICE_SPEED_HS = 2,
    USB_DEVICE_SPEED_UNDEF = 0,
}UsbDeviceSpeed_t;

typedef enum{
    USB_HOST_SPEED_FS = 1,
    USB_HOST_SPEED_HS = 2,
    USB_HOST_SPEED_UNDEF=0,
}UsbHostSpeed_t;

typedef enum{
    USB_MCAL_ROLE_DEVICE = 1,
    USB_MCAL_ROLE_HOST = 2,
    USB_MCAL_ROLE_UNDEF = 0,
}UsbRole_t;


#endif /* USB_GENERAL_CONST_H */
