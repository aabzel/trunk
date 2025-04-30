#ifndef USB_TYPES_H
#define USB_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_USB
#error "+HAS_USB"
#endif

typedef struct{
    uint8_t usb_num;
    bool valid;
#ifdef HAS_USB_DEVICE

#endif /*HAS_USB_DEVICE*/


    uint8_t low_level_core_index;
    char name[20];
}UsbConfig_t;

typedef struct{


#ifdef HAS_USB_DEVICE

#endif /*HAS_USB_DEVICE*/
    uint8_t usb_num;
    bool valid;
}UsbHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* USB_TYPES_H */

