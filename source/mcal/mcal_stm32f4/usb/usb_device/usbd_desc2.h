#ifndef USB_DEVICE_DESC_H
#define USB_DEVICE_DESC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "usbd_def.h"

#define DEVICE_ID1          (UID_BASE)
#define DEVICE_ID2          (UID_BASE + 0x4)
#define DEVICE_ID3          (UID_BASE + 0x8)

#define USB_SIZ_STRING_SERIAL       0x1A

extern USBD_DescriptorsTypeDef USB_Dev_Desc;

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_DESC_H */

