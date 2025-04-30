#ifndef UART_CONFIG_H
#define UART_CONFIG_H

#ifndef HAS_UART
#error "+HAS_UART"
#endif

#include "sys_config.h"
#include "uart_types.h"

#ifdef HAS_CLI
#include "cli_config.h"
#endif

extern const UartConfig_t UartConfig[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* UART_CONFIG_H  */
