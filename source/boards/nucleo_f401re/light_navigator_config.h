
#ifndef LIGHT_NAVIGATOR_CONFIG_H
#define LIGHT_NAVIGATOR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "light_navigator_types.h"

#ifndef HAS_LIGHT_NAVIGATOR
#error "+HAS_LIGHT_NAVIGATOR"
#endif

extern const LightNavigatorConfig_t LightNavigatorConfig[];
extern LightNavigatorHandle_t LightNavigatorInstance[];

uint32_t light_navigator_get_cnt(void);

#endif /* LIGHT_NAVIGATOR_CONFIG_H */
