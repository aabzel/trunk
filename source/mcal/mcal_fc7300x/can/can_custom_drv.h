#ifndef CAN_CUSTOM_DRV_H
#define CAN_CUSTOM_DRV_H

#include "microcontroller_const.h"
#include "can_mcal.h"
#include "can_custom_isr.h"
#include "can_custom_types.h"
#include "flexcan_hw_access.h"

CanIdentifier_t CanFc73MsgIdTypeToIdType(flexcan_msgbuff_id_type_t msgIdType);
uint32_t can_wakeup_message_buffer_id_get(uint8_t num, uint32_t mb_idx);
bool can_move_info_get(uint8_t num, uint8_t message_buffer_num) ;
bool can_message_buffer_interrupt_get(uint8_t num,uint8_t message_buffer_num);
//flexcan_time_segment_t CanBitRateToBitRate(uint32_t bit_rate) ;

#endif /* CAN_CUSTOM_DRV_H  */
