#ifndef CALIBRATION_DATA_COMMANDS_H
#define CALIBRATION_DATA_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool cmd_calibration_data_init(int32_t argc, char* argv[]);
bool cmd_calibration_data_get(int32_t argc, char* argv[]);

#define CALIBRATION_DATA_BASE_COMMANDS                                                                 \
    SHELL_CMD("calibration_data_init", "cdin", cmd_calibration_data_init, "CalibDataInit"),            \
    SHELL_CMD("calibration_data_get", "cdg", cmd_calibration_data_get, "CalibDataGet"),

#ifdef HAS_CALIBRATION_DATA_WRITE
bool cmd_calibration_data_set(int32_t argc, char* argv[]);
bool cmd_calibration_data_erase(int32_t argc, char* argv[]);

#define CALIBRATION_DATA_WRITE_COMMANDS                                                                           \
    SHELL_CMD("calibration_data_set", "cds", cmd_calibration_data_set, "CalibDataSet"),                           \
    SHELL_CMD("calibration_data_erase", "cde", cmd_calibration_data_erase, "CalibDataErase"),

#else
#define CALIBRATION_DATA_WRITE_COMMANDS
#endif

#define CALIBRATION_DATA_COMMANDS                                          \
    CALIBRATION_DATA_BASE_COMMANDS                                         \
    CALIBRATION_DATA_WRITE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* CALIBRATION_DATA_COMMANDS_H */
