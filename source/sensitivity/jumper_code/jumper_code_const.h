#ifndef JUMPER_CODE_CONST_H
#define JUMPER_CODE_CONST_H

#include "time_mcal.h"
#include "jumper_code_dep.h"

#define JUMPER_CODE_VERSION 2
#define JUMPER_CODE_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    JUMPER_CODE_STATE_UNDEF = 0,
    JUMPER_CODE_STATE_0 = 1,
    JUMPER_CODE_STATE_1 = 2,
    JUMPER_CODE_STATE_2 = 3,
}JumperCodeState_t;


typedef enum {
    JUMPER_CODE_VARIABLE1_UNDEF ,
    JUMPER_CODE_VARIABLE1_VALUE_1 ,
    JUMPER_CODE_VARIABLE1_VALUE_2 ,
}JumperCodeVariable1_t;



#endif /* JUMPER_CODE_CONST_H */
