#ifndef USB_CUSTOM_TYPES_H
#define USB_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "usb_const.h"
#include "stm32f4xx_hal_pcd.h"

#ifdef HAS_USB_SERIAL
#include "usb_serial_types.h"
#else
#define USB_SERIAL_VARIABLE
#endif

#ifdef HAS_USB_DEVICE
#include "usbd_def.h"
#endif

#ifdef HAS_USB_HOST
#include "usbh_def.h"
#endif

#ifdef HAS_USB_DEVICE
#define USB_DEVICE_CUSTOM_VARIABLE                  \
    USB_SERIAL_VARIABLE                             \
    USBD_ClassTypeDef* usbd_hid;                    \
    PCD_HandleTypeDef PcdHandle;                    \
    USBD_HandleTypeDef hUsbDevice;

#else
#define USB_DEVICE_CUSTOM_VARIABLE
#endif


#ifdef HAS_USB_HOST
#define USB_HOST_CUSTOM_VARIABLE                \
    USBH_ClassTypeDef* hid_class;               \
    bool host_init_done;                        \
    USBH_HandleTypeDef hUsbHost;                \
    HCD_HandleTypeDef hhcd_USB_OTG;

#else
#define USB_HOST_CUSTOM_VARIABLE
#endif

#define USB_DEVIVE_CONFIG_CUSTOM_VARIABLE     \
        USBD_DescriptorsTypeDef* Descriptors;

#define USB_CONFIG_CUSTOM_VARIABLE          \
        USB_DEVIVE_CONFIG_CUSTOM_VARIABLE

#define USB_CUSTOM_VARIABLE     \
    USB_HOST_CUSTOM_VARIABLE    \
    USB_DEVICE_CUSTOM_VARIABLE

typedef struct {
    uint8_t num;
    bool valid;
    USB_OTG_GlobalTypeDef * USBx;
}UsbInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* USB_CUSTOM_TYPES_H */

