#ifndef SYSTICK_CONFIG_H
#define SYSTICK_CONFIG_H

#include "systick_types.h"

#ifndef HAS_MICROCONTROLLER
#error  "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_SYSTICK
#error  "+HAS_SYSTICK"
#endif

#ifndef HAS_CORTEX_M
#error  "+HAS_CORTEX_M"
#endif

extern const SysTickConfig_t SysTickConfig;
extern SysTick_t SysTickItem;

#endif /* SYSTICK_CONFIG_H */
