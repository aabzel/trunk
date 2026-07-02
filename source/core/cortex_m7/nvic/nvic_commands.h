#ifndef NVIC_COMMANDS_H
#define NVIC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifndef HAS_NVIC_COMMANDS
#error "+HAS_NVIC_COMMANDS"
#endif /*HAS_NVIC_COMMANDS*/

bool nvic_enable_irq_command(int32_t argc, char* argv[]);
bool nvic_enable_command(int32_t argc, char* argv[]) ;
bool nvic_diag_command(int32_t argc, char* argv[]) ;
bool nvic_get_command(int32_t argc, char* argv[]) ;
bool nvic_set_command(int32_t argc, char* argv[]) ;

#define NVIC_COMMANDS                                                               \
    SHELL_CMD("nvic_diag", "nd", nvic_diag_command, "IntDiag"),                     \
    SHELL_CMD("nvic_en_irq", "nen", nvic_enable_irq_command, "IntEnIrq"),           \
    SHELL_CMD("nvic_en", "ne", nvic_enable_command, "IntEnable"),                   \
    SHELL_CMD("nvic_set", "ns", nvic_set_command, "IntSet"),                        \
    SHELL_CMD("nvic_get", "ng", nvic_get_command, "IntGet"),

#ifdef __cplusplus
}
#endif

#endif /* NVIC_COMMANDS_H */
