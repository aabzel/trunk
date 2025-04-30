#ifndef DS_TWR_CONST_H
#define DS_TWR_CONST_H

#include "ds_twr_dependencies.h"
#include "time_mcal.h"

#define DS_TWR_PERIOD_US MSEC_2_USEC(1)
#define DS_TWR_TIME_OUT SEC_2_MSEC(1) /*long 2*/

typedef enum {
    DS_TWR_EVENT_RX_POLL   =1,
    DS_TWR_EVENT_RX_POLL_RESP   =2,
    DS_TWR_EVENT_RX_RESPONSE   =3,
    DS_TWR_EVENT_RX_TIMING   =4,
    DS_TWR_EVENT_UNDEF   =0,
} DsTwrEvent_t;


typedef enum {
    DS_TWR_IDLE = 0,
    DS_TWR_INITIATOR_LOOP = 2,
    DS_TWR_INITIATOR_DELAY = 3,
    DS_TWR_INITIATOR_WAIT_TIMING = 4,
    DS_TWR_RESPONDER_DELAY = 5,
    DS_TWR_RESPONDER_LOOP = 6,
    DS_TWR_DONE = 8,

    DS_TWR_UNDEF = 10,
} DsTwrState_t;

typedef enum {
    DS_TWR_INPUT_NONE = 0,
    DS_TWR_INPUT_START = 1,
    DS_TWR_INPUT_RX_TIME_STAMP = 2,
    DS_TWR_INPUT_TX_TIME_STAMP = 3,
    DS_TWR_INPUT_TIME_OUT = 5,
    DS_TWR_INPUT_RX_POLL = 6, /*From Initiator to responder*/
    DS_TWR_INPUT_RX_RESPONSE = 7,
    DS_TWR_INPUT_RX_PESPONSE_POLL = 8,
    DS_TWR_INPUT_RX_PESPONDER_TIMINGS = 9,

    DS_TWR_INPUT_UNDEF = 10,
} DsTwrInput_t;

#endif /* DS_TWR_CONST_H  */
