#ifndef BLACK_BOX_COMMAND_H
#define BLACK_BOX_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool black_box_diag_command(int32_t argc, char *argv[]);

#define BLACK_BOX_COMMANDS                                                       \
   SHELL_CMD("black_box_diag", "dbd", black_box_diag_command, "BlackBoxDiag"),

#endif /* BLACK_BOX_COMMAND_H */
