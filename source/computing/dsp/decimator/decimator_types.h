#ifndef DECIMATOR_TYPES_H
#define DECIMATOR_TYPES_H

#include <std_includes.h>

#include "decimator_const.h"
#include "sensitivity_const.h"


#define DECIMATOR_COMMON_VARIABLES                    \
    uint32_t num;                                     \
    uint32_t samples_per_bit;                         \
    char* name;                                       \
    bool valid;

typedef struct {
    DECIMATOR_COMMON_VARIABLES
} DecimatorConfig_t;

typedef struct {
    DECIMATOR_COMMON_VARIABLES
    bool init;
    bool valid_data; // spot valid bit
    int8_t value;
    int8_t data_out; // extracted data bit after decimation
    uint32_t samples_cnt;
    DecimatorState_t state;
    DecimatorInput_t input;
    DecimatorState_t prev_state;
} DecimatorHandle_t;

#endif /* DECIMATOR_TYPES_H  */
