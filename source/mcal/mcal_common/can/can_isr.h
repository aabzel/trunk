#ifndef CAN_MCAL_ISR_H
#define CAN_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_types.h"

bool can_isr_ll(CanHandle_t* Node);
bool can_isr_error_ll( CanHandle_t* Node);
bool can_isr_rx_done_ll( CanHandle_t* Node ) ;
bool can_isr_tx_done_ll( CanHandle_t* Node ) ;

bool can_isr(uint32_t num);
bool can_isr_error(uint32_t num);
bool can_isr_rx_done(uint32_t num);
bool can_isr_tx_done(uint32_t num);

#ifdef __cplusplus
}
#endif

#endif /* CAN_MCAL_ISR_H */
