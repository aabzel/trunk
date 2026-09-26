#ifndef BIN_ADC_CONST_H
#define BIN_ADC_CONST_H

#include "time_mcal.h"
#include "bin_adc_dep.h"

#define BIN_ADC_VERSION 2
#define BIN_ADC_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    BIN_ADC_STATE_0 = 1,
    BIN_ADC_STATE_1 = 2,
    BIN_ADC_STATE_2 = 3,
    BIN_ADC_STATE_UNDEF = 0,
}BinAdcState_t;


#endif /* BIN_ADC_CONST_H */
