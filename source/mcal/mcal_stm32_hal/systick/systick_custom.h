#ifndef STM32_SYSTICK_H
#define STM32_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

//bool systick_disable(void);
bool systick_hal_suspend(void);
bool systick_set_period_ms(uint32_t period_ms);
bool systick_custom_init(void);
uint32_t systick_get_period_ms(void);

#ifdef __cplusplus
}
#endif

#endif // STM32_SYSTICK_H
