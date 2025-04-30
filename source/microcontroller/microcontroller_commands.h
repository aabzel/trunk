#ifndef MICROCONTROLLER_COMMANDS_H
#define MICROCONTROLLER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_MCU_CUSTOM_COMMANDS
#include "mcu_custom_commands.h"
#else
#define MCU_CUSTOM_COMMANDS
#endif

#define MICROCONTROLLER_COMMANDS MCU_CUSTOM_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* MICROCONTROLLER_COMMANDS_H */
