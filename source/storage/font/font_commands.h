#ifndef FONT_COMMAND_H
#define FONT_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool font_diag_char_command(int32_t argc, char *argv[]);
bool font_diag_char_raw_command(int32_t argc, char *argv[]);

#define FONT_COMMANDS                                                       \
    SHELL_CMD("font_diag_char", "fdc", font_diag_char_command, "FontDiagChar"), \
    SHELL_CMD("font_diag_char_raw", "fdcr", font_diag_char_raw_command, "FontDiagCharRaw"),

#endif /* FONT_COMMAND_H */
