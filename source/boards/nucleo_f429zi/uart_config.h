#ifndef UARTS_CONFIG_H
#define UARTS_CONFIG_H

#include "uart_types.h"
#include "sys_config.h"

#ifdef HAS_BC127
#define UART_NUM_BC127 2
#define BC127_UART_BAUD_RATE 9600 /* bit/s */
#endif

#ifdef HAS_CLI
#include "cli_config.h"
#endif

#if defined(HAS_CLI) && defined(HAS_BC127)
#define UART_NUM 2
#else
#ifdef HAS_CLI
#define UART_NUM 1
#endif /*HAS_CLI*/
#endif /*HAS_CLI and  HAS_BC127*/

#define BC127_UART_RX_FIFO_SIZE 200 /* byte */

extern const UartConfig_t UartConfigLuT[UART_NUM];
extern UartHandle_t UartInstance[UART_NUM];

uint32_t uart_get_cnt(void);

#endif /* UARTS_CONFIG_H  */
