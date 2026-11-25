#ifndef CAN_CUSTOM_ISR_H
#define CAN_CUSTOM_ISR_H

#include "std_inc.h"
#include "module_driver_flexcan.h"
#include "can_node.h"

int32_t canCustomRxHandler( canNode_t* const pNode, FLEXCAN_RxMsgType const * const pRxMsg );

void CAN0_IRQHandler(void) ;
void CAN1_IRQHandler(void) ;
void CAN2_IRQHandler(void) ;
void CAN3_IRQHandler(void) ;
void CAN4_IRQHandler(void) ;
void CAN5_IRQHandler(void) ;
void CAN6_IRQHandler(void) ;
void CAN7_IRQHandler(void) ;
void CAN8_IRQHandler(void) ;
void CAN9_IRQHandler(void) ;

#endif /* CAN_CUSTOM_ISR_H */
