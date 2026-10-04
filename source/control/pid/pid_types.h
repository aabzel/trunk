#ifndef PID_TYPES_H
#define PID_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pid_constants.h"
#include "sensitivity_const.h"
#include "storage_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#define PID_COMMON_VARIABLE             \
    uint8_t num;                        \
    bool on;                            \
    StorageUnits_t units;               \
    float period_s;                     \
    uint8_t adc_channel_num;            \
    uint8_t pwm_dac_num;                \
    bool valid;                         \
    bool manual;                        \
    float target;                       \
    float p;                            \
    float i;                            \
    float d;                            \
    char* name;

typedef struct {
    PID_COMMON_VARIABLE
} PidConfig_t;

typedef struct {
    PID_COMMON_VARIABLE
    float out;
    float error;
    float last_target;
    float error_prev;
    float d_sum;
    float error_diff;
    float shift; /*Deviation from the last target*/
    float error_sum;
    float read;
    bool init;
    uint64_t next_us;
} PidHandle_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*PID_TYPES_H*/
