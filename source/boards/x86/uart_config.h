#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "uart_types.h"
#include "sys_config.h"

#define LOG_UART_NUM 1
#define UART_MAX_NUM 0

extern const UartConfig_t UartConfig[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* USART_CONFIG_H  */
