#ifndef CAN_CUSTOM_TYPE_H
#define CAN_CUSTOM_TYPE_H

#include "artery_at32f4xx.h"
#include "can_custom_const.h"

#define CAN_CUSTOM_VARIABLES \
    can_type* CANx;

typedef struct{
    uint8_t num;
    crm_periph_clock_type clock_type;
    IRQn_Type irq_n;
    can_type* CANx;
    bool valid;
    ClockBus_t clock_bus;
    uint32_t clock_hz;
    IRQn_Type irqn_tx;
    IRQn_Type irqn_rx0;
    IRQn_Type irqn_rx1;
    IRQn_Type irqn_sce; //Status error interrupt
}CanInfo_t;


#endif /* CAN_CUSTOM_TYPE_H  */
