#ifndef CAN_CALL_BACKS_H
#define CAN_CALL_BACKS_H

#include "can_mcal.h"

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef* hcan) ;

void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef* hcan) ;
void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef* hcan);

void HAL_CAN_TxMailbox0AbortCallback(CAN_HandleTypeDef* hcan);
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef* hcan);

void HAL_CAN_TxMailbox1AbortCallback(CAN_HandleTypeDef* hcan);
void HAL_CAN_TxMailbox2AbortCallback(CAN_HandleTypeDef* hcan) ;

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef* hcan);
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef* hcan) ;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan);
void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef* hcan);

void HAL_CAN_WakeUpFromRxMsgCallback(CAN_HandleTypeDef* hcan);
void HAL_CAN_SleepCallback(CAN_HandleTypeDef* hcan);


#endif /* CAN_CALL_BACKS_H  */
