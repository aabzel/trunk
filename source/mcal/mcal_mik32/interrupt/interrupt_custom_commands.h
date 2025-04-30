#ifndef INTERRUPT_CUSTOM_COMMANDS_H
#define INTERRUPT_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_raw_reg_command(int32_t argc, char* argv[]);
bool interrupt_custom_enable_irq_command(int32_t argc, char* argv[]);
bool interrupt_custom_enable_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_diag_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_get_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_set_command(int32_t argc, char* argv[]) ;

#define INTERRUPT_CUSTOM_COMMANDS                                             \
    SHELL_CMD("int_raw_reg", "irr", interrupt_raw_reg_command, "IntRawReg"),

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_CUSTOM_COMMANDS_H */
