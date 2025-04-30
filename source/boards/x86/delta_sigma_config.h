#ifndef DELTA_SIGMA_CONFIG_H
#define DELTA_SIGMA_CONFIG_H

#include <stdbool.h>

#include "delta_sigma_types.h"

extern const DeltaSigmaConfig_t DeltaSigmaConfig[];
extern DeltaSigmaHandle_t DeltaSigmaInstance[];

uint32_t delta_sigma_get_cnt(void);

#endif /* DELTA_SIGMA_CONFIG_H  */
