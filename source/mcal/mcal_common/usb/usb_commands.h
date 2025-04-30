#ifndef USB_COMMANDS_H
#define USB_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_USB
#error "+HAS_USB"
#endif

#ifndef HAS_USB_COMMANDS
#error "+HAS_USB_COMMANDS"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_USB_COMMANDS
#include "usb_custom_commands.h"
#else /*HAS_USB_COMMANDS*/
#define USB_CUSTOM_COMMANDS
#endif /*HAS_USB_COMMANDS*/

#define USB_COMMANDS           \
    USB_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* USB_COMMANDS_H */
