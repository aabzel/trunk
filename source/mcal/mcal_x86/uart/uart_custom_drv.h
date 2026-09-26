#ifndef USART_CUSTOM_DRV_H
#define USART_CUSTOM_DRV_H

#include "uart_mcal.h"
#include "microcontroller_const.h"
#include "module_driver_fcuart.h"
#include "uart_custom_types.h"
#include "uart_custom_diag.h"
#include "uart_custom_isr.h"

uint32_t UartGetBaseClock(uint8_t num) ;
bool UartRetToRes(FCUART_ErrorType ret) ;

#endif /* USART_CUSTOM_DRV_H  */
