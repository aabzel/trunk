#ifndef BUTTON_FSM_CONST_H
#define BUTTON_FSM_CONST_H

#include "std_includes.h"

#include "button_dep.h"

#define BUTTON_POLL_PERIOD_US 300000
#define BUTTON_LONG_PRESS_TIMEOUT_MS 3000

typedef enum {
    BUTTON_STATE_UNPRESSED = 0,
    BUTTON_STATE_PRESSED = 1,
    BUTTON_STATE_PRESSED_PROCESSED = 2,
    BUTTON_STATE_ERROR = 3,

    BUTTON_STATE_UNDEF = 4,
} ButtonState_t;


typedef enum {
    BUTTON_IN_PASSIVE = 0,
    BUTTON_IN_ACTIVE = 1,
    BUTTON_IN_TIME_OUT = 2,
    BUTTON_IN_NOP = 3,

    BUTTON_IN_UNDEF = 4,
} ButtonInput_t;

typedef enum {
    BUTTON_PRESS_SHORT = 1,
    BUTTON_PRESS_LONG = 2,

    BUTTON_PRESS_UNDEF = 0,
} ButtonPressType_t;


#endif /* BUTTON_FSM_CONST_H  */
