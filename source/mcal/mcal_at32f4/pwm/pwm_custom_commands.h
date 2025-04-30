#ifndef PWM_CUSTOM_COMMANDS_H
#define PWM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifndef HAS_PWM
#error "+HAS_PWM"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_PWM_COMMANDS
#error "+HAS_PWM_COMMANDS"
#endif


#define PWM_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* PWM_CUSTOM_COMMANDS_H */
