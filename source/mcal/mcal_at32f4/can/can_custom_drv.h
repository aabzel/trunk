#ifndef CAN_CUSTOM_DRV_H
#define CAN_CUSTOM_DRV_H

#include "microcontroller_const.h"
#include "can_mcal.h"
#include "can_custom_isr.h"
#include "can_custom_types.h"

bool CanAt32MsgToCanMsg(can_rx_message_type* At32Message,  CanMessage_t* Generalessage );
bool can_wait_tx_done(CanHandle_t* Node, can_tx_mailbox_num_type transmit_mailbox);

#endif /* CAN_CUSTOM_DRV_H  */
