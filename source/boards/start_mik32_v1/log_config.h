#ifndef LOG_CONFIG_H
#define LOG_CONFIG_H

#include "log_types.h"

#define LOG_UART_NUM 0

extern const LogConfig_t LogConfig[];
extern LogHandle_t LogInstance[];

bool log_fix(void);
uint32_t log_get_cnt(void);

#endif /*LOG_CONFIG_H*/
