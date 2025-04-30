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
    SHELL_CMD("nvic_diag", "id", nvic_diag_command, "NvicDiag"),           \
    SHELL_CMD("nvic_en_irq", "ien", nvic_enable_irq_command, "NvicEnIrq"),           \
    SHELL_CMD("nvic_en", "ie", nvic_enable_command, "NvicEnable"),         \
    SHELL_CMD("nvic_set", "is", nvic_set_command, "NvicSet"),              \
    SHELL_CMD("nvic_get", "ig", nvic_get_command, "NvicGet"),

#ifdef __cplusplus
}
#endif

#endif /* NVIC_COMMANDS_H */
