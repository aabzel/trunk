#ifndef USB_MCAL_H
#define USB_MCAL_H

#include <stdbool.h>

#include "usb_config.h"
#include "usb_types.h"
#include "usb_diag.h"

#ifdef HAS_USB_CUSTOM
#include "usb_custom_drv.h"
#endif

#ifdef HAS_USB_DEVICE
#include "usbd_conf.h"
#endif

#ifdef HAS_USB_HOST
#include "usbh_conf.h"
#endif

/*API*/
UsbHandle_t* UsbGetNode(uint8_t usb_num);
const UsbConfig_t* UsbGetConfig(uint8_t num);
bool UsbIsValidConfig(const UsbConfig_t* const Config);

bool usb_mcal_init(void);
bool usb_init_custom(void);
bool usb_init_common(const UsbConfig_t* const Config, UsbHandle_t* const Node) ;

bool usb_proc_custom(void);
bool usb_proc_one(uint8_t usb_num);
bool usb_proc(void);

/*  set  */
bool usb_re_plug(const uint8_t usb_num);

#endif /* USB_MCAL_H */
