#ifndef USB_SERIAL_COMMANDS_H
#define USB_SERIAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool usb_serial_diag_command(int32_t argc, char* argv[]);
bool usb_serial_send_command(int32_t argc, char* argv[]);

#define USB_SERIAL_COMMANDS                                                                       \
    SHELL_CMD("usb_serial_send", "uss", usb_serial_send_command, "UsbSerialSend"),                \
    SHELL_CMD("usb_serial_diag", "usd", usb_serial_diag_command, "UsbSerialDiag"),

#ifdef __cplusplus
}
#endif

#endif /* USB_SERIAL_COMMANDS_H */
