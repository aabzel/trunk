#ifndef BOARD_COMMANDS_H
#define BOARD_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_BOARD
#error "+HAS_BOARD"
#endif

bool reboot_keyboard_command(int32_t argc, char* argv[]);

#define BOARD_COMMANDS                                                       \
    SHELL_CMD("reboot_keyboard", "kbr", reboot_keyboard_command, "BoardRebootKeyBoard"),


#ifdef __cplusplus
}
#endif

#endif /* BOARD_COMMANDS_H */
