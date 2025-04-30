
#ifndef CROSS_DETECT_CONST_H
#define CROSS_DETECT_CONST_H

#include "cross_detect_dep.h"
#include "time_mcal.h"

#define ONE_STATE_TIME_OUT_MS 333
#define CROSS_DETECT_TRY_PER_PAIR 3

#define CROSS_DETECT_POLL_PERIOD_US MSEC_2_USEC(100)

typedef enum {
    CONF_NO = 1,
    CONF_MAYBE = 2,
    CONF_YES = 3,

    CONF_UNDEF=0,
}ConfidenceLevel_t;

/*State */
typedef enum {
    CROSS_DETECT_STATE_LA_RA = 0, /*Left Pull air   ,Right pull air*/
    CROSS_DETECT_STATE_LU_RA = 1, /*Left pull up,	,Right pull air*/
    CROSS_DETECT_STATE_LD_RA = 2, /*Left pull down	,Right pull air*/
    CROSS_DETECT_STATE_LD_RD = 3, /*Left pull down	,Right pull down*/
    CROSS_DETECT_STATE_LD_RU = 4, /*Left pull down	,Right pull up*/
    CROSS_DETECT_STATE_LA_RU = 5, /*Left pull air	,Right pull up*/
    CROSS_DETECT_STATE_LU_RU = 6, /*Left pull up	,Right pull up*/
    CROSS_DETECT_STATE_LU_RD = 7, /*Left pull up	,Right pull down*/
    CROSS_DETECT_STATE_LA_RD = 8, /*Left pull air	,Right pull down*/

    CROSS_DETECT_STATE_UNDEF = 9, /**/
}CrossDetectState_t;

typedef enum {
    READ_L0_R0 = 0,
    READ_L0_R1 = 1,
    READ_L1_R0 = 2,
    READ_L1_R1 = 3,

    READ_UNDEF = 4,
}CrossDetectGpioRead_t;

/*Solution of cross for pin pair*/
typedef enum {
    CROSS_DETECT_SOL_LEFT_SHORT_GND = 1,
    CROSS_DETECT_SOL_LEFT_SHORT_VCC = 2,
    CROSS_DETECT_SOL_RIGHT_SHORT_GND = 3,
    CROSS_DETECT_SOL_RIGHT_SHORT_VCC = 4,
    CROSS_DETECT_SOL_LEFT_OPEN = 5,
    CROSS_DETECT_SOL_RIGHT_OPEN = 6,
    CROSS_DETECT_SOL_OPEN = 7,
    CROSS_DETECT_SOL_CROSS = 8,

    CROSS_DETECT_SOL_UNDEF = 0,
} CrossDetectSolution_t;

#endif /* CROSS_DETECT_CONST_H  */
