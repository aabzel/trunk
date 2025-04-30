#ifndef MULTIMEDIA_COMMANDS_H
#define MULTIMEDIA_COMMANDS_H

#ifdef HAS_LOG
#include "log.h"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_MULTIMEDIA
#error "+HAS_MULTIMEDIA"
#endif

#ifndef HAS_MULTIMEDIA_COMMANDS
#error "+HAS_MULTIMEDIA_COMMANDS"
#endif

#ifdef HAS_AUDIO_USB_COMMANDS
#include "audio_usb_commands.h"
#else
#define AUDIO_USB_COMMANDS
#endif

#ifdef HAS_DAC_COMMANDS
#include "dac_commands.h"
#else
#define DAC_COMMANDS
#endif

#if defined(HAS_WM8731) && defined(HAS_BT1024)
bool cmd_multimedia_bt1024_wm8731_fwd(int32_t argc, char* argv[]);

#define MULTIMEDIA_FWD_COMMANDS                                                        \
    SHELL_CMD("bt1026_wm8731_fwd", "bwf", cmd_multimedia_bt1024_wm8731_fwd, "Bt1026Wm8731"),
#else
#define MULTIMEDIA_FWD_COMMANDS
#endif

bool play_1kHz_tone_command(int32_t argc, char* argv[]);

#define MULTIMEDIA_COMMANDS                                                     \
    SHELL_CMD("play_1kHz_tone", "pt", play_1kHz_tone_command, "PlayTone1kHz"),  \
    MULTIMEDIA_FWD_COMMANDS                                                     \
    AUDIO_USB_COMMANDS


#endif /* MULTIMEDIA_COMMANDS_H */
