#ifndef PID_COMMANDS_H
#define PID_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool pid_diag_command(int32_t argc, char* argv[]);
bool pid_target_command(int32_t argc, char* argv[]);
bool pid_ctrl_command(int32_t argc, char* argv[]);
bool pid_p_command(int32_t argc, char* argv[]);
bool pid_i_command(int32_t argc, char* argv[]);
bool pid_d_command(int32_t argc, char* argv[]);
bool pid_init_command(int32_t argc, char* argv[]);

#define PID_COMMANDS                                                  \
      SHELL_CMD("pid_target", "pidt", pid_target_command, "PidTarget"),     \
      SHELL_CMD("pid_ctrl", "pt", pid_ctrl_command, "PidControl"),     \
      SHELL_CMD("pid_diag", "pid", pid_diag_command, "PidDiag"),     \
      SHELL_CMD("pid_init", "pidn", pid_init_command, "PidInit"),     \
      SHELL_CMD("pid_p", "pidp", pid_p_command, "PidP"),     \
      SHELL_CMD("pid_i", "pidi", pid_i_command, "PidI"),     \
      SHELL_CMD("pid_d", "pidd", pid_d_command, "PidD"),

#ifdef __cplusplus
}
#endif

#endif /* PID_COMMANDS_H  */
