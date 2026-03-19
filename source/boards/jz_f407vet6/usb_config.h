#ifndef USB_CONFIG_H
#define USB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_types.h"
#include "std_includes.h"

typedef enum {
    USB_DEVICE_NUM = 1,
    USB_HOST_NUM = 2,
}UsbLegalNums_t;

extern const UsbConfig_t UsbConfig[];
extern UsbHandle_t UsbInstance[];

uint32_t usb_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_CONFIG_H */

