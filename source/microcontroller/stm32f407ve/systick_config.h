#ifndef SYSTICK_CONFIG_H
#define SYSTICK_CONFIG_H

#include "systick_types.h"

extern const SysTickConfig_t SysTickConfig[];
extern SysTickHandle_t SysTickInstance[];

uint32_t systick_get_cnt(void);

#endif /* SYSTICK_CONFIG_H */
