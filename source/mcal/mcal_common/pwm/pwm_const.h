#ifndef PWM_CONST_H
#define PWM_CONST_H

#include "pwm_dep.h"

#if 0
typedef enum {
    PWM_CHANNEL_0 = 0,
    PWM_CHANNEL_1 = 1,
    PWM_CHANNEL_2 = 2,
    PWM_CHANNEL_3 = 3,
    PWM_CHANNEL_4 = 4,
    PWM_CHANNEL_5 = 5,

    PWM_CHANNEL_UNDEF = 0x55,
} PwmChannel_t;
#endif

typedef enum {
    PWM_MODE_OFF = 0,
    PWM_MODE_ON = 1,
    PWM_MODE_FREQ_MUX = 2, /*frequency multiplexing mode*/

    PWM_MODE_UNDEF = 0x55,
} PwmMode_t;

typedef enum {
    PWM_POLARITY_LOW = 1,
    PWM_POLARITY_HIGH = 2,
    PWM_POLARITY_UNDEF = 0,
} PwmPolarity_t;




#endif /* PWM_CONST_H */
