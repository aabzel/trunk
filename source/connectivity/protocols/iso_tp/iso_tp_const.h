#ifndef ISO_TP_CONSTANTS_H
#define ISO_TP_CONSTANTS_H

/*ISO_TP */
#ifdef __cplusplus
extern "C" {
#endif

#include "iso_tp_dep.h"

#define ISO_TP_PERIOD_US 1000
#define ISO_TP_MTU 4095
#define ISO_TP_PADDING_BYTE 0xAA

typedef enum {
    ISO_TP_FRAME_CODE_SINGLE_FRAME=0,
    ISO_TP_FRAME_CODE_FIRST_FRAME=1,
    ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME=2,
    ISO_TP_FRAME_CODE_FLOW_CONTOL=3,

    ISO_TP_FRAME_CODE_UNDEF = 4,
} IsoTpFrameCode_t;

typedef enum {
    FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND=0,
    FLOW_CONRTOL_FLAG_WAIT=1,
    FLOW_CONRTOL_FLAG_OVERFLOW=2,

    FLOW_CONRTOL_FLAG_UNDEF=3,
} IsoTpFlowControlFlag_t;

typedef enum {
    ISO_TP_STATE_IDLE = 1,
    ISO_TP_STATE_WAIT_FLOW_CONTROL = 2,
    ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME= 3,
	ISO_TP_STATE_TX_REST= 4,


    ISO_TP_STATE_UNDEF = 0,
} IsoTpState_t;


typedef enum {
    ISO_TP_ROLE_SENDER = 1,
    ISO_TP_ROLE_RECEIVER = 2,

    ISO_TP_ROLE_UNDEF = 0,
} IsoTpRole_t;


typedef enum {
    ISO_TP_BUFF_TX= 1,
    ISO_TP_BUFF_RX= 2,

    ISO_TP_BUFF_UNDEF = 0,
} IsoTpBuff_t;


#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_CONSTANTS_H */
