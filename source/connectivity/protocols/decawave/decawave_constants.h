#ifndef DECAWAVE_PROTOCOL_CONSTANTS_H
#define DECAWAVE_PROTOCOL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "decawave_dep.h"

#define DECAWAVE_MAX_FRAME 100                                              /*byte*/
#define DECAWAVE_HEADER_SIZE 10                                             /*byte*/
#define DECAWAVE_FRAME_MIN_SIZE 12                                          /*byte*/
#define DECAWAVE_MAX_PAYLOAD (DECAWAVE_MAX_FRAME - DECAWAVE_FRAME_MIN_SIZE) /*byte*/
#define DECAWAVE_PAYLOAD_INDEX 10
#define DECAWAVE_FCS_SIZE 2

/*Message type*/
typedef enum {
    DECA_BLINK = 0xC5,
    DECA_RANGING_INIT = 0x20,
    DECA_POLL = 0x61,
    DECA_RESP = 0x50,
    DECA_RESP_POLL = 0x65,
    // DECA_POLL_RESP = 0x66,
    DECA_FINAL = 0x69,

    DECA_UNDEF = 0x00,
} DwcaMess_t;

typedef enum {
    UWB_VAR_INITIATOR_T_LOOP = 1,
    UWB_VAR_INITIATOR_T_DELAY = 4,
    UWB_VAR_RESPONDER_T_DELAY = 2,
    UWB_VAR_RESPONDER_T_LOOP = 3,
    UWB_VAR_RESPONDER_TIMINGS = 5,
    UWB_VAR_SHARE_DIST = 7,
    UWB_VAR_RAW_DATA = 6,
    UWB_VAR_LACK = 7,

    UWB_VAR_UNDEF = 0,
} UwbVatiable_t;

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_PROTOCOL_CONSTANTS_H */
