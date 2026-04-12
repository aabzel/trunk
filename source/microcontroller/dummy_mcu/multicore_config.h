#ifndef MULTICORE_CONFIG_H
#define MULTICORE_CONFIG_H

#include "multicore_types.h"
#include "std_includes.h"

extern const MultiCoreConfig_t MultiCoreConfig[];
extern MultiCoreHandle_t MultiCoreInstance[];

uint32_t multicore_get_cnt(void);

#endif /*MULTICORE_CONFIG_H*/
