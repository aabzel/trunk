#ifndef MCO_DRV_H
#define MCO_DRV_H

#include "mco_types.h"
#include "mik32_hal.h"
#include "sys_config.h"

bool mco_init(void);
bool mco_config(McoChannel_t ch, FrequencySource_t freq, uint8_t divider);

#endif /* MCO_DRV_H  */
