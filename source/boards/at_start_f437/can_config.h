#ifndef CAN_CONFIG_H
#define CAN_CONFIG_H

#include "can_types.h"
#include "sys_config.h"

extern const CanConfig_t CanConfig[];
extern CanHandle_t CanInstance[];

uint32_t can_get_cnt(void);

#endif /* CAN_CONFIG_H  */
