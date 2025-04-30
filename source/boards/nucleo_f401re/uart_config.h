#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#include "sys_config.h"
#include "uart_types.h"

#ifdef HAS_CLI
#define UART_NUM_CLI 2
#define CLI_UART_BAUD_RATE 460800 /* bit/s */
#endif

#ifdef HAS_CLI
#define UART_NUM 1
#endif /*HAS_CLI*/

extern const UartConfig_t UartConfigLuT[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* USART_CONFIG_H  */
