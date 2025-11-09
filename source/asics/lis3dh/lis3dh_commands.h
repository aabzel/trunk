#ifndef LIS3DH_COMMANDS_H
#define LIS3DH_COMMANDS_H

#include "std_includes.h"
#include "diag_dep.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_LIS3DH
#error "+ HAS_LIS3DH"
#endif

#ifndef HAS_LIS3DH_COMMANDS
#error "+ HAS_LIS3DH_COMMANDS"
#endif

bool lis3dh_accel_read_command(int32_t argc, char* argv[]) ;
bool lis3dh_log_command(int32_t argc, char* argv[]) ;
bool lis3dh_reg_map_hidden_command(int32_t argc, char* argv[]) ;
bool lis3dh_diag_hl_command(int32_t argc, char* argv[]);
bool lis3dh_diag_low_level_command(int32_t argc, char* argv[]);
bool lis3dh_i2c_ping_command(int32_t argc, char* argv[]);
bool lis3dh_init_command(int32_t argc, char* argv[]);
bool lis3dh_reg_write_command(int32_t argc, char* argv[]);
bool lis3dh_reg_read_command(int32_t argc, char* argv[]);
bool lis3dh_reg_map_command(int32_t argc, char* argv[]);
bool lis3dh_reset_command(int32_t argc, char* argv[]);

#define LIS3DH_COMMANDS                                                                           \
        SHELL_CMD("lis3dh_accel_read", "lia", lis3dh_accel_read_command, "Lis3dhAccelRead"),        \
        SHELL_CMD("lis3dh_log", "lil", lis3dh_log_command, "Lis3dhLog"),        \
        SHELL_CMD("lis3dh_reset", "lir", lis3dh_reset_command, "Lis3dhReset"),        \
        SHELL_CMD("lis3dh_read", "lirr", lis3dh_reg_read_command, "Lis3dhRegRead"),     \
        SHELL_CMD("lis3dh_ping", "lip", lis3dh_i2c_ping_command, "Lis3dhPing"),        \
        SHELL_CMD("lis3dh_map", "lirm", lis3dh_reg_map_command, "Lis3dhRegMap"),        \
        SHELL_CMD("lis3dh_write", "liw", lis3dh_reg_write_command, "Lis3dhRegWrite"),  \
        SHELL_CMD("lis3dh_diag_ll", "adl", lis3dh_diag_low_level_command, "Lis3dhDiagLowLevel"), \
        SHELL_CMD("lis3dh_diag_hi_lev", "lid", lis3dh_diag_hl_command, "Lis3dhDiagHiLevel"),    \
        SHELL_CMD("lis3dh_init", "lii", lis3dh_init_command, "Lis3dhInit"),


#ifdef __cplusplus
}
#endif

#endif /* LIS3DH_COMMANDS_H */
