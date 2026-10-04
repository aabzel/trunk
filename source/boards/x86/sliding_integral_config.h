#ifndef SLIDING_INTEGRAL_CONFIG_H
#define SLIDING_INTEGRAL_CONFIG_H

#include "std_includes.h"
#include "sliding_integral_types.h"

extern const SlidingIntegralConfig_t SlidingIntegralConfig[];
extern SlidingIntegralHandle_t SlidingIntegralInstance[];

uint32_t sliding_integral_get_cnt(void);

#endif /* SLIDING_INTEGRAL_CONFIG_H */
