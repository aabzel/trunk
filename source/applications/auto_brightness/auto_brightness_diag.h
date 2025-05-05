#ifndef AUTO_BRIGHTNESS_DIAG_H
#define AUTO_BRIGHTNESS_DIAG_H

#include <stdbool.h>

#include "auto_brightness_types.h"
#include "auto_brightness_config.h"

bool auto_brightness_diag(void);
char const* AutoBrightnessNode2Str(const AutoBrightnessHandle_t* const Node);
bool AutoBrightnessDiagNode(const AutoBrightnessHandle_t* const Node);
bool AutoBrightnessDiagConfig(const AutoBrightnessConfig_t* const Config);

#endif /* AUTO_BRIGHTNESS_DIAG_H */
