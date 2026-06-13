#ifndef SMOOTH_LAMP_CONST_H
#define SMOOTH_LAMP_CONST_H

#include "time_mcal.h"
#include "smooth_lamp_dep.h"

#define SMOOTH_LAMP_VERSION 2
#define SMOOTH_LAMP_PERIOD_US MSEC_2_USEC(2)
#define SMOOTH_LAMP_ON_DURATION_US 20000000


typedef enum{
    SMOOTH_LAPM_TYPE_PWM = 1,
    SMOOTH_LAPM_TYPE_LED = 2,
    SMOOTH_LAPM_TYPE_DRV8870 = 3,
    SMOOTH_LAPM_TYPE_UNDEF = 0,
}SmoothLampType_t;

typedef enum {
    SMOOTH_LAPM_CMD_OFF = 1,
    SMOOTH_LAPM_CMD_ON = 2,
    SMOOTH_LAPM_CMD_UNDEF = 0,
}SmoothLampCmd_t;

#endif /* SMOOTH_LAMP_CONST_H */
