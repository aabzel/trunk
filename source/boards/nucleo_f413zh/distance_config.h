
#ifndef DISTANCE_CONFIG_H
#define DISTANCE_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "distance_types.h"

#ifndef HAS_DISTANCE
#error " +HAS_DISTANCE"
#endif

extern const DistanceConfig_t DistanceConfig[];
extern volatile DistanceHandle_t DistanceInstance[];

uint32_t distance_get_cnt(void);

#endif /* DISTANCE_CONFIG_H */
