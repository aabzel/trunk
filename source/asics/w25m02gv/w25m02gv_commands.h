#ifndef W25M02GV_COMMANDS_H
#define W25M02GV_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_W25M02GV
#error "+ HAS_W25M02GV"
#endif

#ifndef HAS_W25M02GV_COMMANDS
#error "+ HAS_W25M02GV_COMMANDS"
#endif

bool w25m02gv_reg_map_hidden_command(int32_t argc, char* argv[]);
bool w25m02gv_diag_low_level_command(int32_t argc, char* argv[]);
bool w25m02gv_reset_command(int32_t argc, char* argv[]);
bool w25m02gv_diag_hl_command(int32_t argc, char* argv[]);
bool w25m02gv_init_command(int32_t argc, char* argv[]);
bool w25m02gv_spi_ping_command(int32_t argc, char* argv[]);
bool w25m02gv_register_command(int32_t argc, char* argv[]);
bool w25m02gv_reg_map_command(int32_t argc, char* argv[]);

#define W25M02GV_COMMANDS                                                                      \
        SHELL_CMD("w25m02gv_reset", "w25t", w25m02gv_reset_command, "W25m02gvReset"),            \
        SHELL_CMD("w25m02gv_ping", "w25p", w25m02gv_spi_ping_command, "W25m02gvPing"),           \
        SHELL_CMD("w25m02gv_map", "w25rm", w25m02gv_reg_map_command, "W25m02gvRegMap"),          \
        SHELL_CMD("w25m02gv_register", "w25reg", w25m02gv_register_command, "W25m02gvRegister"),     \
        SHELL_CMD("w25m02gv_diag_ll", "w25l", w25m02gv_diag_low_level_command, "W25m02gvDiagLowLevel"),             \
        SHELL_CMD("w25m02gv_diag_hi_lev", "w25h", w25m02gv_diag_hl_command, "W25m02gvDiagHiLevel"),             \
        SHELL_CMD("w25m02gv_init", "w25i", w25m02gv_init_command, "W25m02gvInit"),


#ifdef __cplusplus
}
#endif

#endif /* W25M02GV_COMMANDS_H */
