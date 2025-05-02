#ifndef TBFP_CONSTANTS_H
#define TBFP_CONSTANTS_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include "tbfp_dependencies.h"

#define TBFP_SIZE_CRC 1
#define TBFP_SIZE_LEN 2
#define TBFP_SIZE_SN 2
#define TBFP_SIZE_PREAMBLE 1
#define TBFP_SIZE_RE_TX_CNT 1
#define TBFP_SIZE_FRAME_ID 1

#define TBFP_SIZE_HEADER (TBFP_SIZE_PREAMBLE+TBFP_SIZE_LEN+TBFP_SIZE_SN+TBFP_SIZE_RE_TX_CNT+TBFP_SIZE_FRAME_ID)
#define TBFP_SIZE_OVERHEAD (TBFP_SIZE_HEADER+TBFP_SIZE_CRC)

//#define TBFP_MAX_PAYLOAD (1024+3+2+ 10)

#define TBFP_MAX_FRAME (TBFP_MAX_PAYLOAD+TBFP_SIZE_OVERHEAD)

#define TBFP_PREAMBLE_DFLT 0xA5
// https://docs.google.com/spreadsheets/d/1VAT3Ak7AzcufgvuRHrRVoVfC3nxugFGJR5pyzxL4W7Q/edit#gid=0
#define TBFP_SIZE_ID 1
#define TBFP_SIZE_CRC 1
#define TBFP_RX_TIME_OUT_MS   10000
#define TBFP_RX_TIME_OUT_ITER 40000

#define TBFP_HEARTBEAT_PERIOD_US 10000000

#define TBFP_OVERHEAD_SIZE (sizeof(TbfpHeader_t) + TBFP_SIZE_CRC )


typedef enum {
  TBFP_INDEX_PREAMBLE= 0,
  TBFP_INDEX_RETX =1,
  TBFP_INDEX_FLAGS =1,
  TBFP_INDEX_SER_NUM= 2,
  TBFP_INDEX_LEN= 4,
  TBFP_INDEX_FRAME_ID= 6,
  TBFP_INDEX_PAYLOAD =7,
} TbfpIndex_t;


typedef enum {
    FRAME_ID_UNDEF = 0x00,  /*Unfed payload*/

    FRAME_ID_JUMP = 0x01,   /**/
    FRAME_ID_MEM = 0x02,   /**/
    FRAME_ID_ACK = 0x41,    /*A*/
    FRAME_ID_CHAT = 0x43,   /*C*/
    FRAME_ID_CMD = 0x44,    /*D*/
    FRAME_ID_PING = 0x51,   /*P*/
    FRAME_ID_STORAGE = 0xFC,   /**/
    FRAME_ID_TUNNEL = 0x54, /*T matryoshka*/
    FRAME_ID_PONG = 0x90,   /**/
    FRAME_ID_KEYBOARD = 0x91,   /**/
#ifdef HAS_DECAWAVE
    FRAME_ID_DECAWAVE = 0x67,
    FRAME_ID_DECAWAVE_NATIVE = 0x68,
#endif /*HAS_DECAWARE*/

#ifdef HAS_RTCM3
    FRAME_ID_RTCM3 = 0xD3,  /**/
#endif
} TbfpPayloadId_t;


#ifdef __cplusplus
}
#endif

#endif /* TBFP_CONSTANTS_H */
