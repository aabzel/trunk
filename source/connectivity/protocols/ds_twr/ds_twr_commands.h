#ifndef DS_TWR_COMMANDS_H
#define DS_TWR_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_DS_TWR
#error "+ HAS_DS_TWR"
#endif

#ifndef HAS_DS_TWR_COMMANDS
#error "+HAS_DS_TWR_COMMANDS"
#endif

bool ds_twr_calibrate_command(int32_t argc, char* argv[]);
bool ds_twr_diag_command(int32_t argc, char* argv[]);
bool ds_twr_enable_continuous_command(int32_t argc, char* argv[]);
bool ds_twr_init_command(int32_t argc, char* argv[]);
bool ds_twr_send_poll_command(int32_t argc, char* argv[]);
bool ds_twr_start_command(int32_t argc, char* argv[]);
bool ds_twr_distances_command(int32_t argc, char* argv[]);

#define DS_TWR_COMMANDS                                                                                             \
        SHELL_CMD("ds_twr_distances", "dsdi", ds_twr_distances_command, "DsTwrDistances"),               \
        SHELL_CMD("ds_twr_diag", "dsd", ds_twr_diag_command, "DsTwrRangeDiag"),                                     \
        SHELL_CMD("ds_twr_enable_continuous", "dsec", ds_twr_enable_continuous_command, "DsTwrEnableContinuous"),   \
        SHELL_CMD("ds_twr_send_poll", "dssp", ds_twr_send_poll_command, "DsTwrSendPoll"),                           \
        SHELL_CMD("ds_twr_calibrate", "dcal", ds_twr_calibrate_command, "DsTwrCalibrate"),                          \
        SHELL_CMD("ds_twr_start", "dss", ds_twr_start_command, "DsTwrStart"),                                       \
        SHELL_CMD("ds_twr_init", "dsi", ds_twr_init_command, "DsTwrInit"),

#ifdef __cplusplus
}
#endif

#endif /* DS_TWR_COMMANDS_H */
