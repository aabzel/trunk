#ifndef DISTANCE_CONST_H
#define DISTANCE_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "time_mcal.h"
#include "distance_dep.h"

#define DISTANCE_INFINITY_M (1000.0)
#define DISTANCE_NO_UPDATE_TIME_OUT_MS 10000 /*mili seconds*/
#define DISTANCE_POLL_PERIOD_US MSEC_2_USEC(100)


/*Constants matter*/
typedef enum {
    DISTANCE_STATE_UNKNOWN = 0, /* */
    DISTANCE_STATE_KNOWN = 1,   /* */

    DISTANCE_STATE_UNDEF = 2,
} DistanceState_t;

/*Constants matter*/
typedef enum {
    DISTANCE_INPUT_TIME_OUT = 0,   /* */
    DISTANCE_INPUT_NEW_MEASUREMENT = 1, /* */
    DISTANCE_INPUT_NONE = 2, /* */

    DISTANCE_INPUT_UNDEF = 3,
} DistanceInput_t;

#ifdef __cplusplus
}
#endif

#endif /* DISTANCE_CONST_H */
