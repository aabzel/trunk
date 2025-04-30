#ifndef SYSTICK_CONFIG_H
#define SYSTICK_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "systick_types.h"

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

extern SysTickConfig_t SysTickConfig;
extern SysTick_t SysTickItem;


#ifdef __cplusplus
}
#endif

#endif // SYSTICK_CONFIG_H
