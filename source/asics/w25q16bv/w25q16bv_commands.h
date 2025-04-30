#ifndef W25Q16BV_COMMANDS_H
#define W25Q16BV_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_W25Q16BV
#error "+ HAS_W25Q16BV"
#endif

#ifndef HAS_W25Q16BV_COMMANDS
#error "+ HAS_W25Q16BV_COMMANDS"
#endif

bool w25q16bv_diag_command(int32_t argc, char* argv[]);
bool w25q16bv_init_command(int32_t argc, char* argv[]);
bool w25q16bv_read_command(int32_t argc, char* argv[]);
bool w25q16bv_reg_write_command(int32_t argc, char* argv[]);
bool w25q16bv_reg_map_command(int32_t argc, char* argv[]);
bool w25q16bv_reg_read_command(int32_t argc, char* argv[]);
bool w25q16bv_reset_command(int32_t argc, char* argv[]);
bool w25q16bv_write_command(int32_t argc, char* argv[]);
bool w25q16bv_write_enable_command(int32_t argc, char* argv[]);

#define W25Q16BV_COMMANDS                                                                                                   \
        SHELL_CMD("w25q16bv_analyze", "mx25a", w25q16bv_analyze_command, "W25Analyze"),                                  \
        SHELL_CMD("w25q16bv_read", "mx25rd", w25q16bv_read_command, "W25Read"),                                          \
        SHELL_CMD("w25q16bv_write", "mx25wr", w25q16bv_write_command, "W25Write"),                                       \
        SHELL_CMD("w25q16bv_map", "mx25m", w25q16bv_reg_map_command, "W25RegMap"),                                       \
        SHELL_CMD("w25q16bv_read", "mx25r", w25q16bv_reg_read_command, "W25RegRead"),                                    \
        SHELL_CMD("w25q16bv_write_enable", "mx25we", w25q16bv_write_enable_command, "W25WriteEnable"),                   \
        SHELL_CMD("w25q16bv_write", "mx25w", w25q16bv_reg_write_command, "W25RegWrite"),                                 \
        SHELL_CMD("w25q16bv_diag", "mx25d", w25q16bv_diag_command, "W25Diag"),                                           \
        SHELL_CMD("w25q16bv_init", "mx25i", w25q16bv_init_command, "W25Init"),                                           \
        SHELL_CMD("w25q16bv_reset", "mx25t", w25q16bv_reset_command, "W25Reset"),

#ifdef __cplusplus
}
#endif

#endif /* W25Q16BV_COMMANDS_H */
