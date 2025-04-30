#ifndef HEX_BIN_COMMANDS_H
#define HEX_BIN_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool hex_to_bin_command(int32_t argc, char* argv[]);
bool bin_to_hex_command(int32_t argc, char* argv[]);

#define HEX_BIN_COMMANDS                                                   \
    SHELL_CMD("hex_to_bin", "hb", hex_to_bin_command, "HexToBin"),         \
    SHELL_CMD("bin_to_hex", "bh", bin_to_hex_command, "BinToHex"),

#ifdef __cplusplus
}
#endif

#endif /* HEX_BIN_COMMANDS_H */
