#ifndef DS3231_COMMANDS_H
#define DS3231_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_ds3231_init(int32_t argc, char* argv[]);
bool cmd_ds3231_run(int32_t argc, char* argv[]);
bool cmd_ds3231_reg_map(int32_t argc, char* argv[]);
bool cmd_ds3231_diag(int32_t argc, char* argv[]);
bool cmd_ds3231_get_reg(int32_t argc, char* argv[]);
bool cmd_ds3231_set_reg(int32_t argc, char* argv[]);
bool cmd_ds3231_set_time_date(int32_t argc, char* argv[]);
bool cmd_ds3231_set_time(int32_t argc, char* argv[]);
bool cmd_ds3231_set_date(int32_t argc, char* argv[]);
bool cmd_ds3231_tune(int32_t argc, char* argv[]);

#define DS3231_COMMANDS                                                        \
    SHELL_CMD("ds3231_diag", "dsd", cmd_ds3231_diag, "Ds3231 diag"),           \
    SHELL_CMD("ds3231_tune", "dst", cmd_ds3231_tune, "Ds3231Tune"),           \
    SHELL_CMD("ds3231_run", "dsu", cmd_ds3231_run, "Ds3231Run"),           \
    SHELL_CMD("ds3231_set_time_date", "dss", cmd_ds3231_set_time_date, "Ds3231SetTimeDate"),           \
    SHELL_CMD("ds3231_set_time", "dsst", cmd_ds3231_set_time, "Ds3231SetTime"),           \
    SHELL_CMD("ds3231_set_date", "dssd", cmd_ds3231_set_date, "Ds3231SetDate"),           \
    SHELL_CMD("ds3231_map", "dsm", cmd_ds3231_reg_map, "Ds3231 Map"),          \
    SHELL_CMD("ds3231_init", "dsi", cmd_ds3231_init, "Ds3231Init"),            \
	    SHELL_CMD("ds3231_read", "dsr", cmd_ds3231_get_reg, "Ds3231GetReg"),   \
	    SHELL_CMD("ds3231_write", "dsw", cmd_ds3231_set_reg, "Ds3231SetReg"),  
                                                                            

#ifdef __cplusplus
}
#endif

#endif /* DS3231_COMMANDS_H */
