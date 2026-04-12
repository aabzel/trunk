#ifndef CAN_GEN_CONST_H
#define CAN_GEN_CONST_H

#include "can_dep.h"
#include "time_mcal.h"

#define CAN_PERIOD_US 1
#define CAN_HEARTBEAT_PERIOD_US SEC_2_USEC(50)
#define CAN_FD_HEARTBEAT_PERIOD_US SEC_2_USEC(60)
#define CAN_HEALTH_MONITOR_PERIOD_US SEC_2_USEC(4)

#define CAN_LED_MOVE_TIME_OUT_MS 500
#define CAN_TX_DONE_TIMEOUT_MS 5000
#define CAN_TX_TIME_OUT_MS 200

#define CAN_STD_ID_MAX_VAL 0x7FFU
#define CAN_EXT_ID_MAX_VAL 0x1FFFFFFFU

#ifdef HAS_CAN_FD
#define CAN_MAX_PAYLOAD_SIZE 64
#else
#define CAN_MAX_PAYLOAD_SIZE 8
#endif

typedef enum {
    CAN_CLOCK_SOURCE_PERIPHERAL = 1,   /*  PLL  (e.g. 200MHz)  */
    CAN_CLOCK_SOURCE_OSCILLATOR  = 2,  /*  XTALL (e.g. 24MHz) */

    CAN_CLOCK_SOURCE_UNDEF = 0
}CanClockSource_t  ;

typedef enum {
    CAN_CFG_MODE_COMMUNICATE = 1,
    CAN_CFG_MODE_LOOPBACK = 2,
    CAN_CFG_MODE_LISTENONLY = 3,
    CAN_CFG_MODE_LISTENONLY_LOOPBACK = 4,
    CAN_CFG_MODE_FREEZE = 5,

    CAN_CFG_MODE_UNDEF = 0
} CanMode_t;

typedef enum {
    CAN_PRIORITY_TOP = 0,
    CAN_PRIORITY_HIGHER = 1,
    CAN_PRIORITY_HI = 2,
    CAN_PRIORITY_MEDIUMHI = 3,
    CAN_PRIORITY_MEDIUMLO = 4,
    CAN_PRIORITY_LOW = 5,
    CAN_PRIORITY_LOWER = 6,
    CAN_PRIORITY_LOWEST = 7,
    CAN_PRIORITY_UNDEF = 8,
} CanPriority_t;


typedef enum {
    CAN_FD_DLC_UNDEF = 0
}CanFdDlc_t;


typedef enum {
    CAN_FILTER_ID_ACCESS_ALLOW= 1,
    CAN_FILTER_ID_ACCESS_BAN= 2,
    CAN_FILTER_ID_ACCESS_UNDEF= 0,
}CanFilterIdAccess_t;

typedef enum {
    CAN_DLC_0 = 0,
    CAN_DLC_1 = 1,
    CAN_DLC_2 = 2,
    CAN_DLC_3 = 3,
    CAN_DLC_4 = 4,
    CAN_DLC_5 = 5,
    CAN_DLC_6 = 6,
    CAN_DLC_7 = 7,
    CAN_DLC_8 = 8,
    CAN_DLC_12 = 9,
    CAN_DLC_16 = 10,
    CAN_DLC_20 = 11,
    CAN_DLC_24 = 12,
    CAN_DLC_32 = 13,
    CAN_DLC_48 = 14,
    CAN_DLC_64 = 15,
    CAN_DLC_UNDEF = 16
}CanDlc_t;

typedef enum {
    CAN_FRAME_ID_STANDARD = 1,  /* standard Id (11 bit) */
    CAN_FRAME_ID_EXTENDED = 2,  /* extended Id (29 bit) */
    CAN_FRAME_ID_UNDEF = 0
} CanIdentifier_t;

typedef enum{
    CAN_FD_BIT_RATE_SWITCH_ON = 1,
    CAN_FD_BIT_RATE_SWITCH_OFF = 2,
    CAN_FD_BIT_RATE_SWITCH_UNDEF = 0,
}CanFdBitRateSwitch_t;

typedef enum{
    CAN_MAC_MODE_LEGACY_FIFO = 1,/**/
    CAN_MAC_MODE_ENHANCED_FIFO = 2,/**/
    CAN_MAC_MODE_MESSAGE_BUFFER = 3, /*  MAILBOXES */
    CAN_MAC_PC_EMULATED = 4, /*  */
    CAN_MAC_MODE_UNDEF = 0,
}CanMacMode_t;

typedef enum {
    CAN_TX_FRAME_DATA = 1, /*!< data frame */
    CAN_TX_FRAME_REMOTE = 2,  /*!< remote frame */

    CAN_TX_FRAME_UNDEF = 0
}CanTxFrame_t  ;

#endif /* CAN_GEN_CONST_H */
