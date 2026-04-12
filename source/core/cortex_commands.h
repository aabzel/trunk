#ifndef CORTEX_COMMANDS_H
#define CORTEX_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


#ifdef HAS_CORTEX_M33_COMMANDS
#include "cortex_m33_commands.h"
#else
#define CORTEX_M33_COMMANDS
#endif

#ifdef HAS_CORTEX_M4_COMMANDS
#include "cortex_m4_commands.h"
#else
#define CORTEX_M4_COMMANDS
#endif

#ifdef HAS_CORTEX_M7_COMMANDS
#include "cortex_m7_commands.h"
#else
#define CORTEX_M7_COMMANDS
#endif

#ifdef HAS_MPU_COMMANDS
#include "cortex_mpu_commands.h"
#else
#define CORTEX_MPU_COMMANDS
#endif

#ifdef HAS_NVIC_COMMANDS
#include "nvic_commands.h"
#else
#define NVIC_COMMANDS
#endif


#ifdef HAS_SYSTICK_COMMANDS
#include "systick_commands.h"
#else
#define SYSTICK_COMMANDS
#endif


#ifndef HAS_CLI
#error "+HAS_CLI"
#endif



#define CORE_CORTEX_M_COMMANDS                                                    \
    CORTEX_M4_COMMANDS                                                            \
    CORTEX_M33_COMMANDS                                                           \
    CORTEX_M7_COMMANDS                                                            \
    CORTEX_MPU_COMMANDS                                                           \
    NVIC_COMMANDS                                                          \
    SYSTICK_COMMANDS


#ifdef __cplusplus
}
#endif

#endif /* CORTEX_COMMANDS_H */
