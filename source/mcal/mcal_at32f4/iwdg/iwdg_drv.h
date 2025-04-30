#ifndef WATCHDOG_DRV_H
#define WATCHDOG_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "iwdg_types.h"

extern WatchDog_t WatchDog;

#ifndef HAS_IWDG
#error "+HAS_IWDG"
#endif

bool iwdg_proc(void);
bool iwdg_init(void);
bool iwdg_set_period_ms(uint32_t period_ms);
double iwdg_calc_period_s(uint16_t clock_hz, uint16_t prescaler, uint16_t reload);
uint32_t iwdg_get_period_ms(void);

#endif /* WATCHDOG_DRV_H  */
