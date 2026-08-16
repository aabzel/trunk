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

//typedef float ds_value_t;
typedef float ds_value_t;

#define DELTA_SIGMA_COMMON_VARIABLES          \
    DELTA_SIGMA_COMMON_MCU_VARIABLES          \
    uint32_t sample_frequency_hz;             \
    uint8_t num;                              \
    uint8_t timer_num;                        \
    float target;                             \
    float min;                                \
    float max;                                \
    float comparator_middle;                  \
    char* name;                               \
    bool valid;

typedef struct {
    DELTA_SIGMA_COMMON_VARIABLES
    float sample_time_s;
    float up_time_s;
    float dac_out;
    float error;
    float sum_error;
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
