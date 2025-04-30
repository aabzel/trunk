#ifndef CAN_GEN_CONST_H
#define CAN_GEN_CONST_H

#include "can_dep.h"

#include "time_mcal.h"

#define CAN_PERIOD_US 100
#define CAN_HEARTBEAT_PERIOD_US SEC_2_USEC(5)

#define CAN_TX_DONE_TIMEOUT_MS 5000

typedef enum {
    CAN_CFG_MODE_COMMUNICATE = 0,
    CAN_CFG_MODE_LOOPBACK = 1,
    CAN_CFG_MODE_LISTENONLY = 2,
    CAN_CFG_MODE_LISTENONLY_LOOPBACK = 3,

    CAN_CFG_MODE_UNDEF = 4
} CanMode_t;

typedef enum {
    CAN_FRAME_ID_STANDARD = 0, /* standard Id */
    CAN_FRAME_ID_EXTENDED = 1,  /* extended Id */

    CAN_FRAME_ID_UNDEF = 3
}CanIdentifier_t  ;

typedef enum {
    CAN_TX_FRAME_DATA = 0, /*!< data frame */
    CAN_TX_FRAME_REMOTE = 1,  /*!< remote frame */

    CAN_TX_FRAME_UNDEF = 2
}CanTxFrame_t  ;

#endif /* CAN_GEN_CONST_H */
