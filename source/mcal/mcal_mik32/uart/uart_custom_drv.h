#ifndef USART_CUSTOM_DRV_H
#define USART_CUSTOM_DRV_H

#include "uart_mcal.h"
#include "periphery/uart.h"
//#include "mik32_hal.h"
#include "sys_config.h"
#include "uart_custom_types.h"

uint32_t UartGetBaseClock(uint8_t num);
bool uart_rx_byte_get_ll(UartHandle_t* Node, uint8_t* rx_byte ) ;

#endif /* USART_CUSTOM_DRV_H  */
