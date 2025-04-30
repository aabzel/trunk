#ifndef DISTANCE_TYPES_H
#define DISTANCE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdbool.h>
#include <stdint.h>

#include "distance_const.h"
#include "decawave_types.h"

#define DISTANCE_COMMAN_VARIABLE     \
    bool valid;                      \
    uint8_t debug_led_num;           \
    uint8_t decawave_num;            \
    uint32_t num;                    \

typedef struct {
    DISTANCE_COMMAN_VARIABLE
    DistanceState_t state;
    DistanceInput_t input;
    uint32_t new_dist_time_stamp_ms;
    int32_t ttl_ms;
    double distance_m;
} DistanceHandle_t;

typedef bool (*DistanceActionHandler_t)(DistanceHandle_t* const Node);

typedef struct {
    DISTANCE_COMMAN_VARIABLE
} DistanceConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* DISTANCE_TYPES_H */
