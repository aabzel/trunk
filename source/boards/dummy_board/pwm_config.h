#ifndef PWM_CONFIG_GENERAL_H
#define PWM_CONFIG_GENERAL_H

#include "std_includes.h"

#include "pwm_types.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

typedef enum {
    PWM_NUM_I2S2 = 1,
    PWM_NUM_MCLK = 2,
    PWM_NUM_TEST = 3,
    PWM_NUM_EXT2 = 4,
    PWM_NUM_EXT1 = 5,
    PWM_NUM_ADC2 = 6,
    PWM_NUM_ENS = 7,

    PWM_NUM_UNDEF =0,
}AtStartPwmNum_t;

extern const PwmConfig_t PwmConfig[];
extern PwmHandle_t PwmInstance[];

uint32_t pwm_get_cnt(void);

#endif /* PWM_CONFIG_GENERAL_H  */
