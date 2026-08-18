#ifndef SONAR_CONST_H
#define SONAR_CONST_H

#include "time_mcal.h"
#include "sonar_dep.h"

#define SONAR_PERIOD_US SEC_2_USEC(30)
#define SONAR_DRIVER_VERSION 1U
#define SONAR_TIMEOUT_MS 4000U
#define SONAR_MAX_SPEC 250000U
#define SONAR_PLOT_CONVOLUTION_SCRIPT "plot_csv_file.py"

typedef enum {
    SONAR_STATE_IDLE,
    SONAR_STATE_PLAY_PROBING_SIGNAL,
    SONAR_STATE_TIMEOUT,
    SONAR_STATE_CALC_CORRELATION,
}SonarState_t;

#endif /* SONAR_CONST_H */
