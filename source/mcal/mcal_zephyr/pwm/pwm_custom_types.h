#ifndef PWM_CUSTOM_TYPES_H
#define PWM_CUSTOM_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <zephyr/drivers/pwm.h>

#include "pwm_custom_const.h"

#define PWM_CUSTON_VARIABLES \
    pwm_flags_t flags;

typedef struct{
    uint8_t num;
    bool valid;
    struct device *dev;
}PwmStaticInfo_t;

#endif /* PWM_CUSTOM_TYPES_H  */
