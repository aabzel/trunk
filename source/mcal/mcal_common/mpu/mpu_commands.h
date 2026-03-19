#ifndef MPU_COMMANDS_H
#define MPU_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_MPU_CUSTOM_COMMANDS
#include "mpu_custom_commands.h"
#else
#define MPU_CUSTOM_COMMANDS
#endif


#ifndef HAS_MPU
#error "+ HAS_MPU"
#endif

#ifndef HAS_MPU_COMMANDS
#error "+ HAS_MPU_COMMANDS"
#endif

bool mpu_diag_command(int32_t argc, char* argv[]);
bool mpu_init_command(int32_t argc, char* argv[]);
bool mpu_reg_map_command(int32_t argc, char* argv[]);

#define MPU_COMMANDS                                                                                          \
        MPU_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("mpu_diag", "mpd", mpu_diag_command, "MpuDiag"),                           \
        SHELL_CMD("mpu_init", "mpi", mpu_init_command, "MpuInit"),                           \
        SHELL_CMD("mpu_reg_map", "mprm", mpu_reg_map_command, "MpuRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* MPU_COMMANDS_H */
