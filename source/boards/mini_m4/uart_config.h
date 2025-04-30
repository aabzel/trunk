#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "uart_types.h"
#include "sys_config.h"

#define UART_NUM_CLI 1
#define CLI_UART_BAUD_RATE 460800 /* bit/s */

extern const UartConfig_t UartConfigLuT[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* USART_CONFIG_H  */
