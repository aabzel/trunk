#ifndef BACK_COUNT_CONST_H
#define BACK_COUNT_CONST_H

#include "time_mcal.h"
#include "back_count_dep.h"

#define BACK_COUNT_VERSION 1
#define BACK_COUNT_PERIOD_US MSEC_2_USEC(1)

typedef enum {
    BACK_COUNT_STATE_UNDEF = 0,
    BACK_COUNT_STATE_IDLE ,
    BACK_COUNT_STATE_ON ,
    BACK_COUNT_STATE_OFF ,
}BackCountState_t;


#endif /* BACK_COUNT_CONST_H */
