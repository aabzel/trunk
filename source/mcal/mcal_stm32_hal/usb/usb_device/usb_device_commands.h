#ifndef USB_DEVICE_COMMANDS_H
#define USB_DEVICE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_serial_commands.h"
#include "std_includes.h"
#include "ostream.h"

bool usb_device_diag_command(int32_t argc, char* argv[]);

#define USB_DEVICE_COMMANDS     USB_SERIAL_COMMANDS                                                                  \
    SHELL_CMD("usb_device_diag", "udd", usb_device_diag_command, "UsbDeviceDiag"),

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_COMMANDS_H */
