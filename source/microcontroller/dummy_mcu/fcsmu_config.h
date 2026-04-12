#ifndef FCSMU_CONFIG_H
#define FCSMU_CONFIG_H

#include "fcsmu_types.h"
#include "std_includes.h"

extern const FcsmuConfig_t FcsmuConfig[];
extern FcsmuHandle_t FcsmuInstance[];

uint32_t fcsmu_get_cnt(void);

#endif /*FCSMU_CONFIG_H*/
