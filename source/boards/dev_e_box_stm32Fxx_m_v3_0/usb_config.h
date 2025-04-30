#ifndef USB_CONFIG_H
#define USB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_types.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

extern const UsbConfig_t UsbConfig[];
extern UsbHandle_t UsbInstance[];

#define USB_DEVICE_NUM 1
#define USB_HOST_NUM 2

uint32_t usb_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_CONFIG_H */

