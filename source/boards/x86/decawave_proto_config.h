
#ifndef DECAWAVE_CONFIG_H
#define DECAWAVE_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "decawave_types.h"

#ifndef HAS_DECAWAVE
#error " +HAS_DECAWAVE"
#endif

extern const DecaWaveConfig_t DecaWaveConfig[];
extern DecaWaveHandle_t DecaWaveInstance[];

uint32_t decawave_get_cnt(void);

#endif /* DECAWAVE_CONFIG_H */
