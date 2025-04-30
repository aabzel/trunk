#ifndef USB_DEVICE_DIAG_H
#define USB_DEVICE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "usbd_def.h"

//const char* UsbErr2Str(uint8_t status);
//const char* UsbErr2Str(uint8_t status);
bool usb_device_diag(void);
bool UsbDeviveDiag(const USBD_HandleTypeDef* const UsbDeviceNode) ;

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_DIAG_H */
