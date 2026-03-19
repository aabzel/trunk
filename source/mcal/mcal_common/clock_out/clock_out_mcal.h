#ifndef CLOCK_OUT_MCAL_H
#define CLOCK_OUT_MCAL_H

#include "clock_out_types.h"
#include "clock_out_config.h"
#ifdef HAS_CLOCK_OUT_DIAG
#include "clock_out_diag.h"
#endif

ClockOutHandle_t* ClockOutGetNode(uint8_t num);
const ClockOutConfig_t* ClockOutGetConfig(uint8_t num) ;

bool clock_out_mcal_init(void);
bool clock_out_init_one(uint8_t num);
bool clock_out_init_custom(void);
bool clock_out_init(void);
bool clock_out_set(ClockOutChannel_t ch, ClockOutBus_t bus_clock, uint32_t divider);
bool clock_out_get(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t* freq_hz) ;

#endif /* CLOCK_OUT_MCAL_H  */
