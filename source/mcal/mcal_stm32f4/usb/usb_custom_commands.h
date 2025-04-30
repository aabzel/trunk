#ifndef USB_CUSTOM_COMMANDS_H
#define USB_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_USB_DEVICE_COMMANDS
// compile
#include "usb_device_commands.h"
#else
#define USB_DEVICE_COMMANDS
#endif

#ifdef HAS_USB_HOST_COMMANDS
#include "usb_host_commands.h"
#else
#define USB_HOST_COMMANDS
#endif

#define USB_CUSTOM_COMMANDS       \
    USB_DEVICE_COMMANDS           \
    USB_HOST_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* USB_CUSTOM_COMMANDS_H */
