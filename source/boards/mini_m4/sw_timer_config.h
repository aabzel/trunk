#ifndef SOFTWARE_TIMER_CONFIG_H
#define SOFTWARE_TIMER_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "software_timer_types.h"

#ifndef HAS_SOFTWARE_TIMER
#error "Add HAS_SOFTWARE_TIMER"
#endif /*HAS_SOFTWARE_TIMER*/

#define SW_TIMER_PASTILDA_NUM 1
#define SW_TIMER_TEST_NUM 2

extern const SoftwareTimerConfig_t SoftwareTimerConfig[];
extern SoftwareTimer_t SoftwareTimerInstance[];

uint32_t software_timer_get_cnt(void);

#endif /* SOFTWARE_TIMER_CONFIG_H  */
