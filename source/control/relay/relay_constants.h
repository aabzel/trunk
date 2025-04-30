#ifndef RELAY_CONSTANTS_H
#define RELAY_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "relay_dep.h"
#include "time_mcal.h"

#define RELAY_PERIOD_US MSEC_2_USEC(1)

typedef enum {
    RELAY_STATE_OFF= 1,
    RELAY_STATE_ON = 2,

    RELAY_STATE_UNDEF = 0,
} RelaySate_t;

typedef enum {
    RELAY_MODE_OFF= 1,
    RELAY_MODE_ON = 2,
    RELAY_MODE_BLINK = 3,
    RELAY_MODE_PWM = 4,
    RELAY_MODE_PULSE_TRAIN = 5,

    RELAY_MODE_UNDEF = 0,
} RelayMode_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*RELAY_CONSTANTS_H*/
