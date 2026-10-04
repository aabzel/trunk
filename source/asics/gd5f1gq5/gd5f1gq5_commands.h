#ifndef GD5F1GQ5_COMMANDS_H
#define GD5F1GQ5_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_GD5F1GQ5
#error "+ HAS_GD5F1GQ5"
#endif

#ifndef HAS_GD5F1GQ5_COMMANDS
#error "+ HAS_GD5F1GQ5_COMMANDS"
#endif

bool gd5f1gq5_write_ctrl_command(int32_t argc, char* argv[]);
bool gd5f1gq5_diag_command(int32_t argc, char* argv[]);
bool gd5f1gq5_init_command(int32_t argc, char* argv[]);
bool gd5f1gq5_reg_map_command(int32_t argc, char* argv[]);
bool gd5f1gq5_get_features_command(int32_t argc, char* argv[]);
bool gd5f1gq5_read_cache_command(int32_t argc, char* argv[]);
bool gd5f1gq5_read_to_cache_command(int32_t argc, char* argv[]);
bool gd5f1gq5_read_page_command(int32_t argc, char* argv[]);
bool gd5f1gq5_read_block_command(int32_t argc, char* argv[]);
bool gd5f1gq5_write_page_command(int32_t argc, char* argv[]);
bool gd5f1gq5_block_erase_command(int32_t argc, char* argv[]);

#define GD5F1GQ5_COMMANDS                                                                                              \
        SHELL_CMD("gd5f1gq5_read_block", "gd5rb", gd5f1gq5_read_block_command, "Gd5f1gq5ReadBlock"),                   \
        SHELL_CMD("gd5f1gq5_block_erase", "gd5be", gd5f1gq5_block_erase_command, "Gd5f1gq5BlockErase"),                \
        SHELL_CMD("gd5f1gq5_read_page", "gd5rp", gd5f1gq5_read_page_command, "Gd5f1gq5ReadPage"),                      \
        SHELL_CMD("gd5f1gq5_read_to_cache", "gd5rtc", gd5f1gq5_read_to_cache_command, "Gd5f1gq5ReadToCache"),          \
        SHELL_CMD("gd5f1gq5_read_cache", "gd5rc", gd5f1gq5_read_cache_command, "Gd5f1gq5ReadCache"),         \
        SHELL_CMD("gd5f1gq5_write_ctrl", "gd5wc", gd5f1gq5_write_ctrl_command, "Gd5f1gq5WriteCtrl"),         \
        SHELL_CMD("gd5f1gq5_get_features", "gd5gf", gd5f1gq5_get_features_command, "Gd5f1gq5GetFeature"),    \
        SHELL_CMD("gd5f1gq5_diag", "gd5d", gd5f1gq5_diag_command, "Gd5f1gq5Diag"),                           \
        SHELL_CMD("gd5f1gq5_init", "gd5i", gd5f1gq5_init_command, "Gd5f1gq5Init"),                           \
        SHELL_CMD("gd5f1gq5_write_page", "gd5wp", gd5f1gq5_write_page_command, "Gd5f1gq5WritePage"),         \
        SHELL_CMD("gd5f1gq5_reg_map", "gd5rm", gd5f1gq5_reg_map_command, "Gd5f1gq5RawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* GD5F1GQ5_COMMANDS_H */
