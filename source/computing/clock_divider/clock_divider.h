#ifndef CLOCK_DIVIDER_DRV_H
#define CLOCK_DIVIDER_DRV_H

/*CLOCK_DIVIDER receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "clock_divider_diag.h"
#include "clock_divider_types.h"
#include "clock_divider_config.h"

ClockDividerHandle_t* ClockDividerGetNode(uint8_t num);
const ClockDividerConfig_t* ClockDividerGetConfig(uint8_t num);


bool clock_divider_proc_period(uint8_t num);

bool clock_divider_init_one(uint8_t num);
bool clock_divider_mcal_init(void);
bool clock_divider_set(uint8_t num, uint32_t divider);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*CLOCK_DIVIDER_DRV_H*/
