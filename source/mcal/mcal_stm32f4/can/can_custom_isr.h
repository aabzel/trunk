#ifndef CAN_CUSTOM_ISR_H
#define CAN_CUSTOM_ISR_H

#include "can_mcal.h"

bool CANx_IRQHandler(const uint8_t num);

void HAL_CAN_ErrorCallback( CAN_HandleTypeDef *hcan );

#ifdef HAS_CAN1
#endif


#ifdef HAS_CAN2
#endif




#endif /* CAN_CUSTOM_ISR_H  */
