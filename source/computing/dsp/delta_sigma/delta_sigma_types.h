#ifndef DELTA_SIGMA_DELTA_SIGMA_TYPES_H
#define DELTA_SIGMA_DELTA_SIGMA_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "delta_sigma_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#define DELTA_SIGMA_COMMON_MCU_VARIABLES          \
    Pad_t Pad;

#else
#define DELTA_SIGMA_COMMON_MCU_VARIABLES
#endif

//typedef double ds_value_t;
typedef int32_t ds_value_t;

#define DELTA_SIGMA_COMMON_VARIABLES          \
    DELTA_SIGMA_COMMON_MCU_VARIABLES          \
    uint32_t sample_frequency_hz;             \
    uint8_t num;                              \
    ds_value_t target;    /*mv*/              \
    ds_value_t min; /*mv*/                    \
    ds_value_t max; /*mv*/                    \
    ds_value_t comparator_middle; /*mv*/      \
    char* name;                               \
    bool valid;

typedef struct {
    DELTA_SIGMA_COMMON_VARIABLES
    double sample_time_s;
    double up_time_s;
    ds_value_t dac_out;
    ds_value_t error;
    ds_value_t sum_error;
    uint32_t sample_cnt;
    int8_t pdm;
}DeltaSigmaHandle_t;

typedef struct {
    DELTA_SIGMA_COMMON_VARIABLES
}DeltaSigmaConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* DELTA_SIGMA_DELTA_SIGMA_TYPES_H */
