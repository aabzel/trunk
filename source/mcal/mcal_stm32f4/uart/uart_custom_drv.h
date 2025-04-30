#ifndef USART_CUSTOM_DRV_H
#define USART_CUSTOM_DRV_H

#include "uart_mcal.h"
#include "stm32f4xx_hal.h"
#include "sys_config.h"
#include "uart_custom_types.h"


int8_t get_uart_index(USART_TypeDef* USARTx);

#endif /* USART_CUSTOM_DRV_H  */
