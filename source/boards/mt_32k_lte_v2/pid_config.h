#ifndef PID_CONFIG_H
#define PID_CONFIG_H

#include "pid_types.h"

extern const PidConfig_t PidConfig[];
extern PidHandle_t PidInstance[];

uint32_t pid_get_cnt(void);

#endif /* PID_CONFIG_H  */
