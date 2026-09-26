#ifndef CAN_CUSTOM_TYPE_H
#define CAN_CUSTOM_TYPE_H

#include "can_custom_const.h"
#include "microcontroller_types.h"


#define CAN_CUSTOM_TX_VARIABLES


#define CAN_CUSTOM_RX_VARIABLES

#define CAN_CUSTOM_VARIABLES         \
    CAN_CUSTOM_RX_VARIABLES          \
    CAN_CUSTOM_TX_VARIABLES

typedef struct {
    uint8_t num;
    bool valid;
}CanInfo_t;





#endif /* CAN_CUSTOM_TYPE_H  */
