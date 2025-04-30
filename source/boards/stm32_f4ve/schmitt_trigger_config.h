#ifndef SCHMITT_TRIGGER_CONFIG_H
#define SCHMITT_TRIGGER_CONFIG_H

#include "std_includes.h"
#include "schmitt_trigger_types.h"

extern const SchmittTriggerConfig_t SchmittTriggerConfig[];
extern SchmittTriggerHandle_t SchmittTriggerInstance[];

uint32_t schmitt_trigger_get_cnt(void);

#endif /* SCHMITT_TRIGGER_CONFIG_H  */
