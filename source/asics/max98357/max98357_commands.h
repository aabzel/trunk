#ifndef MAX98357_COMMANDS_H
#define MAX98357_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_MAX98357
#error "+HAS_MAX98357"
#endif

bool max98357_init_command(int32_t argc, char* argv[]);
bool max98357_play_1kHz_tone_command(int32_t argc, char* argv[]);

#define MAX98357_COMMANDS                                                                          \
    SHELL_CMD("max98357_init", "mai", max98357_init_command, "Max98357Init"),                      \
    SHELL_CMD("max98357_play_1khz", "mp1", max98357_play_1kHz_tone_command, "Max98357Play1kHz"),

#ifdef __cplusplus
}
#endif

#endif /* MAX98357_COMMANDS_H */
