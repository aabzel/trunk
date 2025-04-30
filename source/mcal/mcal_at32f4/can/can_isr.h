#ifndef CAN_ISR_H
#define CAN_ISR_H

#include "can_mcal.h"

bool CanSwIRQHandler(uint8_t num);
bool CanRxFifoxIRQHandler(uint8_t num, uint32_t can_flag, can_rx_fifo_num_type rx_fifo_num);
bool CanTxIRQHandler(uint8_t num);

#endif /* CAN_ISR_H  */
