#ifndef AUTO_BRIGHTNESS_COMMAND_H
#define AUTO_BRIGHTNESS_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool auto_brightness_diag_command(int32_t argc, char *argv[]);

#define AUTO_BRIGHTNESS_COMMANDS                                                                  \
    SHELL_CMD("auto_brightness_diag", "abd", auto_brightness_diag_command, "AutoBrightnessDiag"),

#endif /* AUTO_BRIGHTNESS_COMMAND_H */
