#ifndef USB_DEVICE_DIAG_H
#define USB_DEVICE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

const char* UsbErr2Str(uint8_t status);

bool usb_device_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_DIAG_H */
