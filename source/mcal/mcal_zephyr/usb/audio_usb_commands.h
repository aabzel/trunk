#ifndef AUDIO_USB_COMMANDS_H
#define AUDIO_USB_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_AUDIO_USB
#error "+HAS_AUDIO_USB"
#endif


bool audio_usb_init_command(int32_t argc, char* argv[]);
bool audio_usb_diag_command(int32_t argc, char* argv[]);

#define AUDIO_USB_COMMANDS                                                                                                 \
        SHELL_CMD("audio_usb_init", "aui", audio_usb_init_command, "AudioUsbInit"),                                                  \
        SHELL_CMD("audio_usb_diag", "aud", audio_usb_diag_command, "AudioUsbDiag"),

#ifdef __cplusplus
}
#endif

#endif /* AUDIO_USB_COMMANDS_H */
