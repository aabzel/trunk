#ifndef SENSITIVITY_INITIALIZE_H
#define SENSITIVITY_INITIALIZE_H

#include "std_includes.h"

#ifdef HAS_ACCEL
#include "accelerometer.h"

bool ACCELEROMETER_init(void);

#define ACCELEROMETER_INITIALIZE                    \
    {                                               \
        .init_function = ACCELEROMETER_init,        \
        .name = "TpACCEL",                          \
    },

#else /*HAS_ACCEL*/
#define ACCELEROMETER_INITIALIZE
#endif /*HAS_ACCEL*/

#define SENSITIVITY_INITIALIZE        \
    ACCELEROMETER_INITIALIZE

#endif /* SENSITIVITY_INITIALIZE_H */
