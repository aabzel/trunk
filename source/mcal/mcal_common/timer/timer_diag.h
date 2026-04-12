#ifndef TIMER_MCAL_DIAG_H
#define TIMER_MCAL_DIAG_H

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include <stdint.h>

#include "timer_types.h"

#ifdef HAS_TIMER_CUSTOM
#include "timer_custom_diag.h"
#endif

bool timer_diag_compare(void);
bool timer_diag_compare_complimentary(void);
bool timer_diag(void);
bool timer_diag_ll(void);
bool timer_diag_interrupt(void);
bool timer_channel_diag(void);

bool timer_raw_reg_diag(uint8_t i);
const char *TimerDirToStr(const TimerDir_t code);
const char *TimerConfigToStr(const TimerConfig_t* const Config);
const char *BusClockToStr(uint32_t bus_clock);

#endif /* TIMER_MCAL_DIAG_H */
