#ifndef UARTS_CONFIG_H
#define UARTS_CONFIG_H

#include "uart_types.h"
#include "sys_config.h"

#ifdef HAS_CLI
#include "cli_config.h"
#endif

extern const UartConfig_t UartConfigLuT[];
extern UartHandle_t UartInstance[];

uint32_t uart_get_cnt(void);

#endif /* UARTS_CONFIG_H  */
