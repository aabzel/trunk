#ifndef DISPLAY_COMMANDS_H
#define DISPLAY_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DISPLAY
#error "+ HAS_DISPLAY"
#endif

#ifndef HAS_DISPLAY_COMMANDS
#error "+ HAS_DISPLAY_COMMANDS"
#endif

bool display_diag_command(int32_t argc, char* argv[]);
bool display_inverse_command(int32_t argc, char* argv[]);
bool display_init_command(int32_t argc, char* argv[]);
bool display_print_char(int32_t argc, char* argv[]);
bool display_print_text(int32_t argc, char* argv[]);

#define DISPLAY_COMMANDS                                                                                                \
        SHELL_CMD("display_print_char", "dpc", display_print_char, "DisplayPrintChar"),                                       \
        SHELL_CMD("display_print_text", "dx", display_print_text, "DisplayPrintText"),                                       \
        SHELL_CMD("display_diag", "dd", display_diag_command, "DisplayDiag"),                                           \
        SHELL_CMD("display_init", "di", display_init_command, "DisplayInit"),                                           \

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_COMMANDS_H */
