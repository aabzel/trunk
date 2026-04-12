#ifndef CORTEX_MPU_COMMANDS_H
#define CORTEX_MPU_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CORTEX_MPU
#error "+HAS_CORTEX_MPU"
#endif

#ifndef HAS_MPU_COMMANDS
#error "+HAS_MPU_COMMANDS"
#endif

bool cortex_mpu_region_command(int32_t argc, char* argv[]);
bool cortex_mpu_reg_diag_command(int32_t argc, char* argv[]);
bool cortex_mpu_diag_command(int32_t argc, char* argv[]);
bool cortex_mpu_init_command(int32_t argc, char* argv[]);

#define CORTEX_MPU_COMMANDS                                                                          \
    SHELL_CMD("mpu_reg_diag",  "mpug",  cortex_mpu_reg_diag_command, "CortexMpuRegDiag"),            \
    SHELL_CMD("cortex_mpu_region",    "cmpur",  cortex_mpu_region_command, "CortexMpuRegionDiag"),   \
    SHELL_CMD("cortex_mpu_diag",    "cmpud",  cortex_mpu_diag_command, "CortexMpuDiag"),             \
    SHELL_CMD("cortex_mpu_init",    "cmpui",  cortex_mpu_init_command, "CortexMpuInit"),

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_MPU_COMMANDS_H */
