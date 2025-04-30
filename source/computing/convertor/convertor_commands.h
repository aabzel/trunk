#ifndef CONVERTOR_COMMANDS_H
#define CONVERTOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CONVERTOR
#error "+ HAS_CONVERTOR"
#endif /*HAS_CONVERTOR*/

#ifndef HAS_CONVERTOR_COMMANDS
#error "+ HAS_CONVERTOR_COMMANDS"
#endif /*HAS_CONVERTOR_COMMANDS*/

bool convertor_hex_command(int32_t argc, char* argv[]);
bool convertor_dec_command(int32_t argc, char* argv[]);
bool convertor_bin_command(int32_t argc, char* argv[]);
bool convertor_oct_command(int32_t argc, char* argv[]);
bool convertor_float_command(int32_t argc, char* argv[]);

#define CONVERTOR_COMMANDS                                                                  \
    SHELL_CMD("convertor_float", "cf", convertor_float_command, "ConvertFloat"),            \
    SHELL_CMD("convertor_hex", "ch", convertor_hex_command, "ConvertHex"),                  \
    SHELL_CMD("convertor_dec", "cd", convertor_dec_command, "ConvertDec"),                  \
    SHELL_CMD("convertor_bin", "cb", convertor_bin_command, "ConvertBin"),                  \
    SHELL_CMD("convertor_oct", "co", convertor_oct_command, "ConvertOct"),

#ifdef __cplusplus
}
#endif

#endif /* CONVERTOR_COMMANDS_H */
