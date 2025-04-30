#ifndef RTOS_COMMAND_H
#define RTOS_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool rtos_diag_command(int32_t argc, char *argv[]);

#define RTOS_COMMANDS                               \
      SHELL_CMD("rtos_diag", "rtd", rtos_diag_command, "FreeRTOSDiag"),

#endif /* RTOS_COMMAND_H */
