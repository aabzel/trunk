#ifndef SW_UART_CONFIG_H
#define SW_UART_CONFIG_H

#include "sw_uart_types.h"

extern const SwUartConfig_t SwUartConfig[];
extern SwUartHandle_t SwUartInstance[];

uint32_t sw_uart_get_cnt(void);

#endif /* SW_UART_CONFIG_H  */
