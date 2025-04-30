#ifndef CORRELATOR_CONFIG_H
#define CORRELATOR_CONFIG_H

#include "std_includes.h"
#include "correlator_types.h"

extern const CorrelatorConfig_t CorrelatorConfig[];
extern CorrelatorHandle_t CorrelatorInstance[];

uint32_t correlator_get_cnt(void);

#endif /* CORRELATOR_CONFIG_H */
