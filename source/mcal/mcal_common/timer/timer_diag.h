#ifndef TIMER_MCAL_DIAG_H
#define TIMER_MCAL_DIAG_H

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif

#include <stdint.h>

#include "timer_types.h"
#include "timer_custom_diag.h"

bool timer_diag_compare(void);
bool timer_diag_compare_complimentary(void);
bool timer_diag(void);
bool timer_diag_ll(void);
bool timer_channel_diag(void);

const char *TimerDirToStr(TimerDir_t code);
const char *TimerConfigToStr(const TimerConfig_t* const Config);
//const char *BusClock2Str(uint32_t bus_clock);

#endif /* TIMER_MCAL_DIAG_H */
