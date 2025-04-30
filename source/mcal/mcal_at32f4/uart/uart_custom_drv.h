#ifndef USART_CUSTOM_DRV_H
#define USART_CUSTOM_DRV_H

#include "microcontroller_const.h"
#include "uart_mcal.h"
#include "uart_custom_types.h"

uint32_t UartGetBaseClock(uint8_t num) ;
int8_t get_uart_index(usart_type* USARTx) ;

#endif /* USART_CUSTOM_DRV_H  */
