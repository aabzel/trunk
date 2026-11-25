#ifndef CAN_CUSTOM_ISR_H
#define CAN_CUSTOM_ISR_H

#include "can_mcal.h"

bool CanSwIRQHandler(uint8_t num);
bool CanTxIRQHandler(uint8_t num);

#endif /* CAN_CUSTOM_ISR_H  */
