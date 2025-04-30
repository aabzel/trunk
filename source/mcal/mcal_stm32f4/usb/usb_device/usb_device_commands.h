#ifndef USB_DEVICE_COMMANDS_H
#define USB_DEVICE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"
// compile
bool hid_keyboard_send_text_command(int32_t argc, char* argv[]);
bool hid_keyboard_send_ll_command(int32_t argc, char* argv[]);
bool hid_keyboard_send_command(int32_t argc, char* argv[]);
bool usb_device_diag_command(int32_t argc, char* argv[]);
bool usb_device_timeout_command(int32_t argc, char* argv[]);

#define USB_DEVICE_COMMANDS                                                                       \
    SHELL_CMD("usb_device_timeout", "udt", usb_device_timeout_command, "UsbDeviceTimeOut"),       \
    SHELL_CMD("usb_device_diag", "udd", usb_device_diag_command, "UsbDeviceDiag"),                \
    SHELL_CMD("hid_key_text", "kt", hid_keyboard_send_text_command, "UsbHidKeySendText"),         \
    SHELL_CMD("hid_key_ll", "hkl", hid_keyboard_send_ll_command, "UsbHidKeySendLowLev"),          \
    SHELL_CMD("hid_key", "ks", hid_keyboard_send_command, "UsbHidKeySend"),

#ifdef __cplusplus
}
#endif

#endif /* USB_DEVICE_COMMANDS_H */
