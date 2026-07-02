#ifndef INTERRUPT_CUSTOM_COMMANDS_H
#define INTERRUPT_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_custom_enable_irq_command(int32_t argc, char* argv[]);
bool interrupt_custom_enable_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_diag_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_get_command(int32_t argc, char* argv[]) ;
bool interrupt_custom_set_command(int32_t argc, char* argv[]) ;

#define INTERRUPT_CUSTOM_COMMANDS                                                    \
    SHELL_CMD("int_diag", "icd", interrupt_custom_diag_command, "IntDiag"),           \
    SHELL_CMD("int_en_irq", "icen", interrupt_custom_enable_irq_command, "IntEnIrq"),           \
    SHELL_CMD("int_en", "ice", interrupt_custom_enable_command, "IntEnable"),         \
    SHELL_CMD("int_set", "ics", interrupt_custom_set_command, "IntSet"),              \
    SHELL_CMD("int_get", "icg", interrupt_custom_get_command, "IntGet"),

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_CUSTOM_COMMANDS_H */
