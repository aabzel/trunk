#ifndef LTR390_COMMANDS_H
#define LTR390_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_LTR390
#error "+ HAS_LTR390"
#endif

#ifndef HAS_I2C_DIAG
#warning "+ HAS_I2C_DIAG"
#endif

#ifndef HAS_LTR390_COMMANDS
#error "+HAS_LTR390_COMMANDS"
#endif

bool ltr390_reset_command(int32_t argc, char* argv[]);
bool ltr390_start_measure_command(int32_t argc, char* argv[]);
bool ltr390_init_command(int32_t argc, char* argv[]);
bool ltr390_diag_command(int32_t argc, char* argv[]);
bool ltr390_reg_map_command(int32_t argc, char* argv[]);
bool ltr390_undoc_reg_map_command(int32_t argc, char* argv[]);

#define LTR390_COMMANDS                                                                                                \
    SHELL_CMD("ltr390_start_measure", "lts", ltr390_start_measure_command, "Ltr390RStart"),                            \
    SHELL_CMD("ltr390_reset", "ltr", ltr390_reset_command, "Ltr390Rreset"),                                            \
    SHELL_CMD("ltr390_diag", "ltd", ltr390_diag_command, "Ltr390Diag"),                                                \
    SHELL_CMD("ltr390_reg_map", "lrm", ltr390_reg_map_command, "Ltr390RegMap"),                                                \
    SHELL_CMD("ltr390_undoc_reg_map", "lturm", ltr390_undoc_reg_map_command, "Ltr390RegMapUndoc"),                     \
    SHELL_CMD("ltr390_init", "lti", ltr390_init_command, "Ltr390Init"),

#ifdef __cplusplus
}
#endif

#endif /* LTR390_COMMANDS_H */
