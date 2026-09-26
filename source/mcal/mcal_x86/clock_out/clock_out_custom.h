#ifndef CLOCK_OUT_DRV_H
#define CLOCK_OUT_DRV_H

#include "clock_out_types.h"
#include "x86x.h"
#include "microcontroller_const.h"

bool clock_out_init(void);
bool clock_out_config(ClockOutChannel_t ch, FrequencySource_t freq, uint8_t divider);

#endif /* CLOCK_OUT_DRV_H  */
