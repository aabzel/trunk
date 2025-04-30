
#ifndef LIGHT_NAVIGATOR_CONFIG_H
#define LIGHT_NAVIGATOR_CONFIG_H

#include <std_includes.h>

#include "light_navigator_types.h"

extern const LightNavigatorConfig_t LightNavigatorConfig[];
extern LightNavigatorHandle_t LightNavigatorInstance[];

uint32_t light_navigator_get_cnt(void);
uint32_t light_navigator_light_to_lambda_get_cnt(void);

#endif /* LIGHT_NAVIGATOR_CONFIG_H */
