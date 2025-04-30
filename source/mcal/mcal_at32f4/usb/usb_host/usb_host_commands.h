#ifndef USB_HOST_COMMANDS_H
#define USB_HOST_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool usb_host_init_command(int32_t argc, char* argv[]);
bool usb_host_diag_command(int32_t argc, char* argv[]);
bool usb_host_led_set_command(int32_t argc, char* argv[]);
bool usb_host_led_get_command(int32_t argc, char* argv[]);
bool usb_host_led_get_test_command(int32_t argc, char* argv[]);
bool usb_host_led_test_command(int32_t argc, char* argv[]);

#define USB_HOST_COMMANDS                                                      \
    SHELL_CMD("usb_host_led_get", "uhlg", usb_host_led_get_command, "UsbHostLedGet"),   \
    SHELL_CMD("usb_host_init", "uhi", usb_host_init_command, "UsbHostInit"),   \
    SHELL_CMD("usb_host_diag", "uhd", usb_host_diag_command, "UsbHostDiag"), \
    SHELL_CMD("usb_host_led_test", "uhlt", usb_host_led_test_command, "UsbHostLedTest"), \
    SHELL_CMD("usb_host_led_get_test", "uhlgt", usb_host_led_get_test_command, "UsbHostLedGetTest"), \
    SHELL_CMD("usb_host_led_set", "uhls", usb_host_led_set_command, "UsbHostLedSet"),

#ifdef __cplusplus
}
#endif

#endif /* USB_HOST_COMMANDS_H */
