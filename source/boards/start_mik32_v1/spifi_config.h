#ifndef SPIFI_CONFIG_GENERAL_H
#define SPIFI_CONFIG_GENERAL_H

#include "std_includes.h"
#include "spifi_types.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

extern const SpiFiConfig_t SpiFiConfig[];
extern SpiFiHandle_t SpiFiInstance[];

uint32_t spifi_get_cnt(void);

#endif /* SPIFI_CONFIG_GENERAL_H  */
