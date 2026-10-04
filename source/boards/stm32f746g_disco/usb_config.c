#include "usb_config.h"

#include "data_utils.h"
#include "usb_types.h"
//#include "usb_const.h"
//#include "usbd_conf.h"
//#include "usbd_desc.h"

#ifndef HAS_USB_DEVICE
#warning +HAS_USB_DEVICE
#endif

const UsbConfig_t SECTION_CFG_DATA UsbConfig[]= {
      {
        .num = 1,
        .speed = USB_MCAL_SPEED_HS,
        .valid = true,
        .name = "Device",
        .device_speed = USB_DEVICE_SPEED_HS,
        .role = USB_MCAL_ROLE_DEVICE,

      },
};

UsbHandle_t UsbInstance[] = {
        { .num = 1, .valid = true, },
};

COMPONENT_GET_CNT(Usb, usb)

