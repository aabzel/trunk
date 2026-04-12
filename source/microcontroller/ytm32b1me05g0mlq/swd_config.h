#ifndef SDW_CONFIG_H
#define SDW_CONFIG_H

#include "swd_types.h"
#include "sys_config.h"

extern const SwdConfig_t SwdConfig[];
extern SwdHandle_t SwdInstance[];

uint32_t swd_get_cnt(void);

#endif /* SDW_CONFIG_H  */
