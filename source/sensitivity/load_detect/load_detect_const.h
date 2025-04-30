
#ifndef LOAD_DETECT_CONST_H
#define LOAD_DETECT_CONST_H

#include "load_detect_dep.h"
#include "time_mcal.h"

#define LOAD_DETECT_PERIOD_US MSEC_2_USEC(10)
#define ONE_STATE_TIME_OUT_MS 333

typedef enum {
    GPIO_CLASS_MCU = 1,
    GPIO_CLASS_DW1000 = 2,
    GPIO_CLASS_DW3000 = 3,

    GPIO_CLASS_UNDEF = 0,
} GpioClass_t;

typedef enum {
    LOAD_DETECT_OUT_OPEN = 1,
    LOAD_DETECT_OUT_SHORT_GND = 2,
    LOAD_DETECT_OUT_SHORT_VCC = 3,

    LOAD_DETECT_OUT_UNDEF = 0,
} LoadDetectOut_t;

#endif /* LOAD_DETECT_CONST_H  */
