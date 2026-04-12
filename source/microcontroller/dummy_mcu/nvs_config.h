#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include "std_includes.h"
#include "nvs_types.h"

extern const NvsConfig_t NvsConfig[];
extern NvsHandle_t NvsInstance[];

uint32_t nvs_get_cnt(void);

#endif /* NVS_CONFIG_H */
