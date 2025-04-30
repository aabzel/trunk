#ifndef PID_TYPES_H
#define PID_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pid_constants.h"
#ifdef HAS_GPIO
#include "gpio_types.h"
#endif
#include "sensitivity_const.h"

#define PID_COMMON_VARIABLE             \
    uint8_t num;                        \
    bool on;                            \
    Units_t unit;                       \
    uint64_t period_us;                 \
    uint8_t adc_channel_num;            \
    uint8_t pwm_dac_num;                \
    bool valid;                         \
    double p;                           \
    double i;                           \
    double d;                           \
    char* name;

typedef struct  {
    PID_COMMON_VARIABLE
} PidConfig_t;

typedef struct  {
    PID_COMMON_VARIABLE
	double out;
	double error;
	double error_prev;
	double error_diff;
	double error_sum;
	double target;
	double read;
    bool init;
    uint64_t next_us;
} PidHandle_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*PID_TYPES_H*/
