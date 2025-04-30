/**
  * This file contains all the function prototypes for
  *          the usb_otg.c file
  */
#ifndef USB_DRV_H
#define USB_STM32_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "usb_types.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

#ifndef HAS_STM32
#error "+HAS_STM32"
#endif

bool usb_init(void);
UsbHandle_t* UsbGetNode(uint8_t usb_num);
UsbHandle_t* UsbGetNodeBySpeed(UsbSpeed_t speed);
const UsbConfig_t* UsbGetConfNode(uint8_t usb_num);

#ifdef __cplusplus
}
#endif

#endif /* USB_STM32_DRV_H */

