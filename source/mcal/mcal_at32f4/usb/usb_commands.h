#ifndef USB_COMMANDS_H
#define USB_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_USB_DEVICE_COMMANDS
#include "usb_device_commands.h"
#else
#define USB_DEVICE_COMMANDS
#endif

#ifdef HAS_USB_HOST_COMMANDS
#include "usb_host_commands.h"
#else
#define USB_HOST_COMMANDS
#endif

#define USB_COMMANDS       \
    USB_DEVICE_COMMANDS    \
    USB_HOST_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* USB_COMMANDS_H */
