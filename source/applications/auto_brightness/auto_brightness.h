#ifndef AUTO_BRIGHTNESS_DRV_H
#define AUTO_BRIGHTNESS_DRV_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "auto_brightness_config.h"
#include "auto_brightness_types.h"

const AutoBrightnessConfig_t* AutoBrightnessGetConfig(uint8_t num);
AutoBrightnessHandle_t* AutoBrightnessGetNode(uint8_t num);

double Dist2Duty(double dist_m);
bool auto_brightness_proc(void);
bool auto_brightness_init(void);
bool auto_brightness_init_one(uint8_t num);
bool auto_brightness_set(AutoBrightnessHandle_t* const Node, double duty_cycle);

#ifdef __cplusplus
}
#endif

#endif /* AUTO_BRIGHTNESS_DRV_H */
