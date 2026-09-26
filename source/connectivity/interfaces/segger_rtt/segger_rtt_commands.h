#ifndef SEGGER_RTT_COMMANDS_H
#define SEGGER_RTT_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SEGGER_RTT
#error "+ HAS_SEGGER_RTT"
#endif

#ifndef HAS_SEGGER_RTT_COMMANDS
#error "+ HAS_SEGGER_RTT_COMMANDS"
#endif

bool segger_rtt_diag_command(int32_t argc, char* argv[]);
bool segger_rtt_init_command(int32_t argc, char* argv[]);
bool segger_rtt_write_command(int32_t argc, char* argv[]);

#define SEGGER_RTT_COMMANDS                                                               \
        SHELL_CMD("segger_rtt_write", "srw", segger_rtt_write_command, "SeggerRttWrite"), \
        SHELL_CMD("segger_rtt_diag", "srd", segger_rtt_diag_command, "SeggerRttDiag"),    \
        SHELL_CMD("segger_rtt_init", "sri", segger_rtt_init_command, "SeggerRttInit"),

#ifdef __cplusplus
}
#endif

#endif /* SEGGER_RTT_COMMANDS_H */
