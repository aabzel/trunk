#ifndef ERM_CONFIG_H
#define ERM_CONFIG_H

#include "erm_types.h"
#include "std_includes.h"

extern const ErmConfig_t ErmConfig[];
extern ErmHandle_t ErmInstance[];

uint32_t erm_get_cnt(void);

#endif /*ERM_CONFIG_H*/
