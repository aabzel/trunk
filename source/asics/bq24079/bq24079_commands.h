#ifndef BQ24079_COMMANDS_H
#define BQ24079_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool bq24079_diag_command(int32_t argc, char* argv[]);
bool bq24079_ctrl_command(int32_t argc, char* argv[]);
bool bq24079_init_command(int32_t argc, char* argv[]);

#define BQ24079_COMMANDS                                                      \
    SHELL_CMD("bq24079_init", "bqi", bq24079_init_command, "Bq24079Diag"),    \
    SHELL_CMD("bq24079_diag", "bqd", bq24079_diag_command, "Bq24079Diag"),    \
    SHELL_CMD("bq24079_ctrl", "bqc", bq24079_ctrl_command, "Bq24079Enable"),

#ifdef __cplusplus
}
#endif

#endif /* BQ24079_COMMANDS_H */
