#ifndef EXT_INT_CONFIG_H
#define EXT_INT_CONFIG_H

#include "ext_int_types.h"
#include "sys_config.h"

extern const ExtIntConfig_t ExtIntConfig[];
extern ExtIntHandle_t ExtIntInstance[];

uint32_t ext_int_get_cnt(void);

#endif /* EXT_INT_CONFIG_H  */
