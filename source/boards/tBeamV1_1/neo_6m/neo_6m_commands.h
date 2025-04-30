#ifndef ZED_F9P_COMMANDS_H
#define ZED_F9P_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool zed_f9p_diag_command(int32_t argc, char* argv[]);
bool zed_f9p_base_dot_command(int32_t argc, char* argv[]);
bool zed_f9p_base_command(int32_t argc, char* argv[]);
bool zed_f9p_rover_command(int32_t argc, char* argv[]);

#define ZED_F9P_COMMANDS                                                                                               \
    SHELL_CMD("zed_f9p_diag", "zfd", zed_f9p_diag_command, "ZEDF9Pdiag"),                                              \
        SHELL_CMD("zed_f9p_base", "zfbd", zed_f9p_base_dot_command, "ZEDF9PbaseDot"),                                  \
        SHELL_CMD("zed_f9p_base", "zfb", zed_f9p_base_command, "ZEDF9Pbase"),                                          \
        SHELL_CMD("zed_f9p_rover", "zfr", zed_f9p_rover_command, "ZEDF9Prover"),

#ifdef __cplusplus
}
#endif

#endif /* ZED_F9P_COMMANDS_H */
