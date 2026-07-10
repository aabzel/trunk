#ifndef REC_PLAY_CONST_H
#define REC_PLAY_CONST_H

#include "time_mcal.h"
#include "rec_play_dep.h"

#define REC_PLAY_VERSION 1
#define REC_PLAY_PERIOD_US MSEC_2_USEC(500)

typedef enum {
    REC_PLAY_STATE_UNDEF = 0,
    REC_PLAY_STATE_IDLE ,
    REC_PLAY_STATE_REC ,
    REC_PLAY_STATE_PLAY ,
}RecPlayState_t;

#endif /* REC_PLAY_CONST_H */
