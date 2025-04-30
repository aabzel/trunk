#ifndef USB_TYPES_H
#define USB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "usb_const.h"

#ifdef HAS_USB_DEVICE
#include "usbd_def.h"
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
#include "usbh_def.h"
#endif /*HAS_USB_HOST*/

#ifndef HAS_USB
#error "+HAS_USB"
#endif

typedef struct{
    uint8_t num;
    bool valid;
#ifdef HAS_USB_DEVICE
    USBD_DescriptorsTypeDef* hs_desc;
    USBD_ClassTypeDef* usbd_hid;
#endif /*HAS_USB_DEVICE*/

#ifdef HAS_USB_HOST
    USBH_ClassTypeDef* hid_class;
#endif
    //uint8_t low_level_core_index;
    char name[20];
    UsbDeviceSpeed_t device_speed;
    UsbHostSpeed_t host_speed;
    UsbSpeed_t speed;
    UsbRole_t role;
}UsbConfig_t;

typedef struct {
	uint32_t prev_init_ms;
#ifdef HAS_USB_HOST
	bool host_init_done;
    USBH_HandleTypeDef hUsbHost;
    HCD_HandleTypeDef hhcd_USB_OTG;
#endif /*HAS_USB_HOST*/

#ifdef HAS_USB_DEVICE
//  PCD_HandleTypeDef usb_h;//hpcd_USB_OTG_HS;
    PCD_HandleTypeDef hpcd_USB_OTG;
    USBD_HandleTypeDef hUsbDevice;
#endif /*HAS_USB_DEVICE*/
    uint8_t num;
    bool valid;
    UsbRole_t role;
    UsbSpeed_t speed;
    UsbDeviceSpeed_t device_speed;
    UsbHostSpeed_t host_speed;
}UsbHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* USB_TYPES_H */

