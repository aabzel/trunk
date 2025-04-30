#ifndef SYSTEM_TIMER_CUSTOM_H
#define SYSTEM_TIMER_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

//bool systick_custom_init(void);
bool systick_set_period_ms(uint32_t period_ms);
uint32_t systick_get_period_ms(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_TIMER_CUSTOM_H
