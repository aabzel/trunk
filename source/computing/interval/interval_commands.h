
#ifndef INTERVAL_COMMANDS_H
#define INTERVAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool interval_shared_command(int32_t argc, char* argv[]);
bool interval_merge_command(int32_t argc, char* argv[]);
bool interval_overlaps_command(int32_t argc, char* argv[]);

#define INTERVAL_COMMANDS                                                    \
    SHELL_CMD("interval_encode", "interval", interval_encode_command, "RleEncode"),     \
    SHELL_CMD("interval_decode", "rld", interval_decode_command, "RleDecode"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*INTERVAL_COMMANDS_H*/
