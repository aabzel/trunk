#ifndef BIN_DAC_CONST_H
#define BIN_DAC_CONST_H

#include "time_mcal.h"
#include "bin_dac_dep.h"

#define BIN_DAC_VERSION 3
#define BIN_DAC_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    BIN_DAC_STATE_0 = 1,
    BIN_DAC_STATE_1 = 2,
    BIN_DAC_STATE_2 = 3,
    BIN_DAC_STATE_UNDEF = 0,
}BinDacState_t;


#endif /* BIN_DAC_CONST_H */
