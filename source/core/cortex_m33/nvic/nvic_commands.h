#ifndef NVIC_COMMANDS_H
#define NVIC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_NVIC_COMMANDS
#error "+HAS_NVIC_COMMANDS"
#endif /*HAS_NVIC_COMMANDS*/

bool nvic_enable_irq_command(int32_t argc, char* argv[]);
bool nvic_enable_command(int32_t argc, char* argv[]) ;
bool nvic_diag_command(int32_t argc, char* argv[]) ;
bool nvic_get_command(int32_t argc, char* argv[]) ;
bool nvic_set_command(int32_t argc, char* argv[]) ;

#define NVIC_COMMANDS                                                    \
    SHELL_CMD("int_diag", "id", nvic_diag_command, "IntDiag"),           \
    SHELL_CMD("int_en_irq", "ien", nvic_enable_irq_command, "IntEnIrq"),           \
    SHELL_CMD("int_en", "ie", nvic_enable_command, "IntEnable"),         \
    SHELL_CMD("int_set", "is", nvic_set_command, "IntSet"),              \
    SHELL_CMD("int_get", "ig", nvic_get_command, "IntGet"),

#ifdef __cplusplus
}
#endif

#endif /* NVIC_COMMANDS_H */
