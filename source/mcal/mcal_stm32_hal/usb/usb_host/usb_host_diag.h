#ifndef USB_HOST_DIAG_H
#define USB_HOST_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "usbh_def.h"

const char* UsbHostStatus2Str( USBH_StatusTypeDef status);
bool usb_host_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_HOST_DIAG_H */
