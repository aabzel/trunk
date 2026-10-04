#ifndef PWM_DAC_CONFIG_H
#define PWM_DAC_CONFIG_H

#include "pwm_dac_types.h"

typedef enum {
    PWM_DAC_TEST = 1,

    PWM_DAC_NUM_UNDEF = 0,
} PwmDac_TeraTestNums_t;

extern const PwmDacConfig_t PwmDacConfig[];
extern PwmDacHandle_t PwmDacInstance[];

uint32_t pwm_dac_get_cnt(void);

#endif /* PWM_DAC_CONFIG_H  */
