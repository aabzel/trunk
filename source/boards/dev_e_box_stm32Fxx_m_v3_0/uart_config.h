#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "uart_types.h"
#include "sys_config.h"


extern const UartConfig_t UartConfig[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* USART_CONFIG_H  */
