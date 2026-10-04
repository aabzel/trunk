#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include "log_types.h"

#define LOG_UART_NUM 2

extern const LogConfig_t LogConfig[];
extern LogHandle_t LogInstance[];

uint32_t log_get_cnt(void);

#endif
