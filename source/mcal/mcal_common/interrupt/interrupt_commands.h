#ifndef INTERRUPT_COMMANDS_H
#define INTERRUPT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "interrupt_custom_commands.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_enable_irq_command(int32_t argc, char* argv[]);
bool interrupt_enable_command(int32_t argc, char* argv[]) ;
bool interrupt_diag_command(int32_t argc, char* argv[]) ;
bool interrupt_get_command(int32_t argc, char* argv[]) ;
bool interrupt_init_command(int32_t argc, char* argv[]) ;
bool interrupt_set_command(int32_t argc, char* argv[]) ;

#define INTERRUPT_COMMANDS                                                               \
    INTERRUPT_CUSTOM_COMMANDS                                                            \
    SHELL_CMD("int_diag", "intd", interrupt_diag_command, "IntDiag"),                    \
    SHELL_CMD("int_init", "inti", interrupt_init_command, "IntInit"),                    \
    SHELL_CMD("int_en_irq", "inten", interrupt_enable_irq_command, "IntEnIrq"),          \
    SHELL_CMD("int_en", "ie", interrupt_enable_command, "IntEnable"),                  \
    SHELL_CMD("int_set", "ints", interrupt_set_command, "IntSet"),                       \
    SHELL_CMD("int_get", "intg", interrupt_get_command, "IntGet"),

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_COMMANDS_H */
