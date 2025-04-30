#ifndef GENERIC_COMMANDS_H
#define GENERIC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool generic_jump_to_bootloader_command(int32_t argc, char* argv[]);

#define GENERIC_COMMANDS                         \
    SHELL_CMD("jump_boot", "jb", generic_jump_to_bootloader_command, "JumpToBoot"),


#ifdef __cplusplus
}
#endif

#endif /* GENERIC_COMMANDS_H */
