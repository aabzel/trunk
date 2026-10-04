#ifndef CLOCK_OUT_CONFIG_H
#define CLOCK_OUT_CONFIG_H

#include "clock_out_types.h"


#ifndef HAS_CLOCK_OUT
#error "+HAS_CLOCK_OUT"
#endif

extern const ClockOutConfig_t ClockOutConfig[];
extern ClockOutHandle_t ClockOutInstance[];

uint32_t clock_out_get_cnt(void);

#endif /* CLOCK_OUT_CONFIG_H  */
