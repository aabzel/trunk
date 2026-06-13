#ifndef PWM_CONFIG_GENERAL_H
#define PWM_CONFIG_GENERAL_H

#include "std_includes.h"
#include "pwm_types.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif

typedef enum {
    PWM_NUM_UNDEF = 0,
    PWM_NUM_DRV8870_CH1_IN1,
    PWM_NUM_DRV8870_CH1_IN2,
    PWM_NUM_LASER_TX,
    PWM_NUM_CNT,
} PwmLegalNums_t;

extern const PwmConfig_t PwmConfig[];
extern PwmHandle_t PwmInstance[];

uint32_t pwm_get_cnt(void);

#endif /* PWM_CONFIG_GENERAL_H  */
