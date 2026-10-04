#ifndef DECIMATOR_CONFIG_H
#define DECIMATOR_CONFIG_H

#include "std_includes.h"
#include "decimator_types.h"

extern const DecimatorConfig_t DecimatorConfig[];
extern DecimatorHandle_t DecimatorInstance[];

uint32_t decimator_get_cnt(void);

#endif /* DECIMATOR_CONFIG_H */
