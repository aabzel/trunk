
#ifndef ZEPHYR_RTOS_CONFIG_H
#define ZEPHYR_RTOS_CONFIG_H

#include "zephyr_rtos_types.h"

extern const RtosTaskConfig_t TaskConfig[];
extern RtosTaskHandle_t TaskInstance[];

uint32_t rtos_task_cnt(void);

#endif /* ZEPHYR_RTOS_CONFIG_H */
