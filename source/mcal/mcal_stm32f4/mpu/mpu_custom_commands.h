#ifndef MPU_CUSTOM_COMMANDS_H
#define MPU_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MPU
#error "+HAS_MPU"
#endif

#ifndef HAS_MPU_COMMANDS
#error "+HAS_MPU_COMMANDS"
#endif

bool mpu_diag_low_level_command(int32_t argc, char* argv[]);

#define MPU_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("mpu_diag_low_level", "mpudl", mpu_diag_low_level_command, "MpuDiagLowLevel"),


#ifdef __cplusplus
}
#endif

#endif /* MPU_CUSTOM_COMMANDS_H */
