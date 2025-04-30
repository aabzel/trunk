
#ifndef RLE_COMMANDS_H
#define RLE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool rle_encode_command(int32_t argc, char* argv[]);
bool rle_decode_command(int32_t argc, char* argv[]);

#define RLE_COMMANDS                                                    \
    SHELL_CMD("rle_encode", "rle", rle_encode_command, "RleEncode"),     \
    SHELL_CMD("rle_decode", "rld", rle_decode_command, "RleDecode"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*RLE_COMMANDS_H*/
