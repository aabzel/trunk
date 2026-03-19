#ifndef USB_GENERAL_TYPES_H
#define USB_GENERAL_TYPES_H

#include "usb_const.h"
#include "std_includes.h"
#include "gpio_types.h"

#ifdef HAS_USB_CUSTOM
#include "usb_custom_types.h"
#else
#define USB_CUSTOM_VARIABLE
#define USB_CONFIG_CUSTOM_VARIABLE
#endif

#define USB_GPIO_VARIABLE                    \
    Pad_t PadDP;                             \
    Pad_t PadDM;

#define USB_COMMON_VARIABLE                  \
    USB_CONFIG_CUSTOM_VARIABLE               \
    USB_GPIO_VARIABLE                        \
    uint32_t tx_buff_size;                   \
    UsbDeviceSpeed_t device_speed;           \
    UsbHostSpeed_t host_speed;               \
    uint8_t num;                             \
    uint8_t* TxFifoArray;                    \
    bool valid;                              \
    UsbRole_t role;                          \
    bool interrupt_on;                       \
    UsbSpeed_t speed;                        \
    char* name;

typedef struct{
    USB_COMMON_VARIABLE
}UsbConfig_t;

typedef struct {
    USB_COMMON_VARIABLE
    USB_CUSTOM_VARIABLE
    uint32_t prev_init_ms;
    bool init;
    uint32_t spin;
    uint32_t tx_cnt;
    bool tx_done;
}UsbHandle_t;

#endif /* USB_GENERAL_TYPES_H */
