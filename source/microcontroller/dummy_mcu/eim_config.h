#ifndef EIM_CONFIG_H
#define EIM_CONFIG_H

#include "eim_types.h"
#include "std_includes.h"

extern const EimConfig_t EimConfig[];
extern EimHandle_t EimInstance[];

uint32_t eim_get_cnt(void);

#endif /*EIM_CONFIG_H*/
