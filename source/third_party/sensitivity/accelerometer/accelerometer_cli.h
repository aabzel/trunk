#ifndef ACCELEROMETER_MONO_COMMANDS_H
#define ACCELEROMETER_MONO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool ACCEL_CalibrateCommand(int32_t argc, char* argv[]);
bool ACCEL_DiagCommand(int32_t argc, char* argv[]);
bool ACCEL_GetCommand(int32_t argc, char* argv[]);
bool ACCEL_InitCommand(int32_t argc, char* argv[]);
bool ACCEL_SaveCalibrateDataCommand(int32_t argc, char* argv[]);

#define ACCELEROMETER_EHAL_COMMANDS                                                             \
    SHELL_CMD("accelerometer_calibrate", "eac", ACCEL_CalibrateCommand, "ACCEL_CalibrateEhal"), \
    SHELL_CMD("accelerometer_diag", "ead", ACCEL_DiagCommand, "ACCEL_Diag"),                    \
    SHELL_CMD("accelerometer_calib_save", "eacs", ACCEL_SaveCalibrateDataCommand, "ACCEL_CalibSave"),  \
    SHELL_CMD("accelerometer_init", "eacci", ACCEL_InitCommand, "ACCEL_InitEhal"),              \
    SHELL_CMD("accelerometer_get", "eaccg", ACCEL_GetCommand, "ACCEL_GetEhal"),

#ifdef __cplusplus
}
#endif

#endif /* ACCELEROMETER_MONO_COMMANDS_H */
