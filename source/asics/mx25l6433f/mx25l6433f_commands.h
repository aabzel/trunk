#ifndef MX25L6433F_COMMANDS_H
#define MX25L6433F_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MX25L6433F
#error "+ HAS_MX25L6433F"
#endif

#ifndef HAS_MX25L6433F_COMMANDS
#error "+ HAS_MX25L6433F_COMMANDS"
#endif

bool mx25l6433f_diag_command(int32_t argc, char* argv[]);
bool mx25l6433f_analyze_command(int32_t argc, char* argv[]);
bool mx25l6433f_init_command(int32_t argc, char* argv[]);
bool mx25l6433f_read_command(int32_t argc, char* argv[]);
bool mx25l6433f_reg_write_command(int32_t argc, char* argv[]);
bool mx25l6433f_reg_map_command(int32_t argc, char* argv[]);
bool mx25l6433f_reg_read_command(int32_t argc, char* argv[]);
bool mx25l6433f_reset_command(int32_t argc, char* argv[]);
bool mx25l6433f_write_command(int32_t argc, char* argv[]);
bool mx25l6433f_write_enable_command(int32_t argc, char* argv[]);

#define MX25L6433F_COMMANDS                                                                                                   \
        SHELL_CMD("mx25l6433f_analyze", "mx25a", mx25l6433f_analyze_command, "Mx25Analyze"),                                  \
        SHELL_CMD("mx25l6433f_read", "mx25rd", mx25l6433f_read_command, "Mx25Read"),                                          \
        SHELL_CMD("mx25l6433f_write", "mx25wr", mx25l6433f_write_command, "Mx25Write"),                                       \
        SHELL_CMD("mx25l6433f_map", "mx25m", mx25l6433f_reg_map_command, "Mx25RegMap"),                                       \
        SHELL_CMD("mx25l6433f_read", "mx25r", mx25l6433f_reg_read_command, "Mx25RegRead"),                                    \
        SHELL_CMD("mx25l6433f_write_enable", "mx25we", mx25l6433f_write_enable_command, "Mx25WriteEnable"),                   \
        SHELL_CMD("mx25l6433f_write", "mx25w", mx25l6433f_reg_write_command, "Mx25RegWrite"),                                 \
        SHELL_CMD("mx25l6433f_diag", "mx25d", mx25l6433f_diag_command, "Mx25Diag"),                                           \
        SHELL_CMD("mx25l6433f_init", "mx25i", mx25l6433f_init_command, "Mx25Init"),                                           \
        SHELL_CMD("mx25l6433f_reset", "mx25t", mx25l6433f_reset_command, "Mx25Reset"),

#ifdef __cplusplus
}
#endif

#endif /* MX25L6433F_COMMANDS_H */
