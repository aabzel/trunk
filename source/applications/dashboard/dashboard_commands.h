#ifndef DASHBOARD_COMMAND_H
#define DASHBOARD_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

bool dashboard_diag_command(int32_t argc, char *argv[]);

#define DASHBOARD_COMMANDS                                                       \
   SHELL_CMD("dashboard_diag", "dbd", dashboard_diag_command, "DashBoardDiag"),

#endif /* DASHBOARD_COMMAND_H */
