#ifndef ISO_TP_CONSTANTS_H
#define ISO_TP_CONSTANTS_H

/*ISO_TP */
#ifdef __cplusplus
extern "C" {
#endif

#include "iso_tp_dep.h"

#define ISO_TP_PERIOD_US 1
//500000
#define ISO_TP_TX_PERIOD_US 700000 //200000 400000
#define ISO_TP_MTU 4095
#define ISO_TP_IDLE_TIME_OUT_MS 800

/*If not specified differently, the default value CC16 should be used for frame padding in order to minimize
 * the stuff-bit insertions and bit alterations on the wire.*/
#define ISO_TP_PADDING_BYTE 0xCC
#define ISO_TP_SEPARATION_TIME_MAX_MS 127
#define ISO_TP_SEPARATION_TIME_CODE_MIN_VAL_0_MS 0x0
#define ISO_TP_SEPARATION_TIME_CODE_MAX_VAL_127_MS 0x7F

typedef enum {
    ISO_TP_FRAME_CODE_SINGLE_FRAME = 0,
    ISO_TP_FRAME_CODE_FIRST_FRAME = 1,
    ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME = 2,
    ISO_TP_FRAME_CODE_FLOW_CONTOL = 3,

    ISO_TP_FRAME_CODE_UNDEF = 4,
} IsoTpFrameCode_t;

typedef enum {
    FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND = 0,
    FLOW_CONRTOL_FLAG_WAIT = 1,
    FLOW_CONRTOL_FLAG_OVERFLOW = 2,

    FLOW_CONRTOL_FLAG_UNDEF = 3,
} IsoTpFlowControlFlag_t;

typedef enum {
    ISO_TP_STATE_IDLE = 1,
    ISO_TP_STATE_WAIT_FLOW_CONTROL = 2,
    ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME = 3,
    ISO_TP_STATE_TX_REST = 4,
    ISO_TP_STATE_UNDEF = 0,
} IsoTpState_t;

typedef enum {
    ISO_TP_ROLE_SENDER = 1,
    ISO_TP_ROLE_RECEIVER = 2,

    ISO_TP_ROLE_UNDEF = 0,
} IsoTpRole_t;

typedef enum {
    ISO_TP_BUFF_TX = 1,
    ISO_TP_BUFF_RX = 2,

    ISO_TP_BUFF_UNDEF = 0,
} IsoTpBuff_t;

/* A.2.6 Protocol data unit format (PF) parameter group number (PGN) */
typedef enum {
    ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA6 = 205, /*mixed addressing: 52480 for N_TAtype = #6, */
    ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA5 = 206, /*mixed addressing: 52736 for N_Tatype = #5, */
    ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA5 = 218, /*normal fixed addressing: 55808 for N_TAtype = #5*/
    ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA6 = 219, /*normal fixed addressing: 56064 for N_TAtype = #6*/
    ISO_TP_PROTOCOL_FORMAT_UNDEF = 0,
} IsoTpProtocolFormat_t;

typedef enum {
    ISO_TP_ADDRESSING_NORMAL = 1,      /* Mapping of N_PDU parameters into CAN frame — Normal addressing*/
    ISO_TP_ADDRESSING_FIXED = 2,       /* Normal fixed addressing, N_TAtype (ID 29-bit)*/
    ISO_TP_ADDRESSING_EXTENDED = 3,    /* Mapping of N_PDU parameters into CAN frame — Extended addressing*/
    ISO_TP_ADDRESSING_MIXED_11BIT = 4, /* Mixed addressing with 11 bit CAN identifier*/
    ISO_TP_ADDRESSING_MIXED_29BIT = 5, /* Mixed addressing with 29 bit CAN identifier*/
    ISO_TP_ADDRESSING_UNDEF = 0,       /* */
} IsoTpAddressing_t;

#ifdef __cplusplus
}
#endif

#endif /* ISO_TP_CONSTANTS_H */
