#ifndef CODE_STYLE_CHECKER_COMMANDS_H
#define CODE_STYLE_CHECKER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool code_style_checker_proto_command(int32_t argc, char* argv[]);
bool code_style_checker_global_proto_command(int32_t argc, char* argv[]);
bool code_style_checker_static_proto_command(int32_t argc, char* argv[]);

#define CODE_STYLE_CHECKER_COMMANDS                                 \
    SHELL_CMD("code_style_checker_proto", "cpr", code_style_checker_proto_command, "CodeStyleCheckProto"),         \
    SHELL_CMD("code_style_checker_static_proto", "csp", code_style_checker_static_proto_command, "CodeStyleCheckStaticProto"),         \
    SHELL_CMD("code_style_checker_check_proto", "cgp", code_style_checker_global_proto_command, "CodeStyleCheckerCheckProto"),


#ifdef __cplusplus
}
#endif

#endif /* CODE_STYLE_CHECKER_COMMANDS_H */
