#ifndef MANCHESTER_DECODE_COMMANDS_H
#define MANCHESTER_DECODE_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MANCHESTER_DECODE
#error "+ HAS_MANCHESTER_DECODE"
#endif

#ifndef HAS_MANCHESTER_DECODE_COMMANDS
#error "+ HAS_MANCHESTER_DECODE_COMMANDS"
#endif

bool manchester_decode_diag_command(int32_t argc, char* argv[]);
bool manchester_decode_init_command(int32_t argc, char* argv[]);

#define MANCHESTER_DECODE_COMMANDS                                                                                          \
        SHELL_CMD("manchester_decode_diag", "mdd", manchester_decode_diag_command, "ManchesterDecodeDiag"),                           \
        SHELL_CMD("manchester_decode_init", "mdi", manchester_decode_init_command, "ManchesterDecodeInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* MANCHESTER_DECODE_COMMANDS_H */
