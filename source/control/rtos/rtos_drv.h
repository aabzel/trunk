#ifndef RTOS_DRV_H
#define RTOS_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "rtos_types.h"
#include "rtos_task_config.h"

RtosTaskHandle_t* RtosTaskGetNode(uint8_t task_num);
const RtosTaskConfig_t* RtosTaskGetConfig(uint8_t task_num);

bool rtos_task_mcal_init(void);
bool rtos_delay_ms(uint32_t delay_ms);

#ifdef __cplusplus
}
#endif

#endif /* RTOS_DRV_H */
