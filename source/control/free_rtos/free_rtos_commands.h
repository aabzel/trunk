#ifndef FREE_RTOS_COMMAND_H
#define FREE_RTOS_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool free_rtos_diag_command(int32_t argc, char *argv[]);

#define FREE_RTOS_COMMANDS                               \
      SHELL_CMD("free_rtos_diag", "ftd", free_rtos_diag_command, "FreeRTOSDiag"),

#endif /* FREE_RTOS_COMMAND_H */
