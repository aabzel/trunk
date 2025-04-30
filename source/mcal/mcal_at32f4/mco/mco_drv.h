#ifndef MCO_DRV_H
#define MCO_DRV_H

#include "mco_types.h"
#include "artery_at32f4xx.h"
#include "microcontroller_const.h"

bool mco_init(void);
bool mco_config(McoChannel_t ch, FrequencySource_t freq, uint8_t divider);

#endif /* MCO_DRV_H  */
