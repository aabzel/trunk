#ifndef SENSITIVITY_ROUTINES_H
#define SENSITIVITY_ROUTINES_H

#include "std_includes.h"

#ifdef HAS_ACCEL_PROC

#include "accelerometer.h"

bool ACCELEROMETER_proc(void);

#define ACCELEROMETER_ROUTINE                                     \
    {                                                             \
        .name = "AccelEhal",                                      \
        .period_us = ACCEL_POLLING_PERIOD_US,                     \
        .limiter.function = ACCELEROMETER_proc,                   \
    },
#else
#define ACCELEROMETER_ROUTINE
#endif

#define SENSITIVITY_ROUTINE     \
    ACCELEROMETER_ROUTINE

#endif /* SENSITIVITY_ROUTINES_H */
