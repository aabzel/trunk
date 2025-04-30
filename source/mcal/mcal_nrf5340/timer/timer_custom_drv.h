#ifndef NRF_TIMER_DRV_H
#define NRF_TIMER_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "sys_config.h"
#include "timer_mcal.h"
#include "timer_const.h"
#include "timer_config.h"
#include "timer_custom_types.h"

uint32_t timer_nrf_get_counter(uint8_t num, CapComChannel_t chaneel);

#endif /* NRF_TIMER_DRV_H  */
