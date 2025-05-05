#ifndef LIGHT_NAVIGATOR_DRV_H
#define LIGHT_NAVIGATOR_DRV_H

#include "std_includes.h"
#include "light_navigator_config.h"
#include "light_navigator_types.h"
#include "light_navigator_diag.h"

const LightNavigatorConfig_t* LightNavigatorGetConfNode(uint8_t num);
LightNavigatorHandle_t* LightNavigatorGetNode(uint8_t num);
bool light_navigator_init_one(uint32_t num);
bool light_navigator_mcal_init(void);
bool light_navigator_light_to_lambda_proc(void);
bool light_navigator_light_to_lambda_proc_one(uint32_t num);
bool light_navigator_check_ll(LightNavigatorHandle_t* const Node);
bool light_navigator_proc(void);
bool light_navigator_proc_one(uint32_t num);
bool light_navigator_proc_all(void);
bool light_navigator_sunrise_proc(uint8_t num);
bool light_navigator_sunset_proc(uint8_t num);

#endif /* LIGHT_NAVIGATOR_DRV_H */
