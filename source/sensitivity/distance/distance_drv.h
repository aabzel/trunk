#ifndef DISTANCE_DRV_H
#define DISTANCE_DRV_H

/*DISTANCE receiver invariant component*/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "distance_config.h"
#include "distance_types.h"

const DistanceConfig_t* DistanceGetConfig(uint8_t num);
bool distance_init(void);
bool distance_init_one(uint8_t num);
bool distance_proc(void);
DistanceHandle_t* DistanceGetNode(uint8_t num);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*DISTANCE_DRV_H*/
