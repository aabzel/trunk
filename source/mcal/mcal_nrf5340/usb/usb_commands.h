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

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif


#define USB_COMMANDS        USB_DEVICE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* USB_COMMANDS_H */
