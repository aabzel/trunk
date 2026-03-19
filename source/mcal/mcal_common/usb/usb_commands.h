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

#ifdef HAS_USB_CUSTOM_COMMANDS
#include "usb_custom_commands.h"
#else
#define USB_CUSTOM_COMMANDS
#endif


bool usb_re_plug_command(int32_t argc, char* argv[]);

#if 0
#define USB_DEVICE_COMMANDS     \
        USB_SERIAL_COMMANDS
#endif


#define USB_COMMANDS                                                     \
    USB_CUSTOM_COMMANDS                                                  \
    SHELL_CMD("usb_re_plug", "urp", usb_re_plug_command, "UsbRePlug"),

#ifdef __cplusplus
}
#endif

#endif /* USB_COMMANDS_H */
