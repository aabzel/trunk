#ifndef LIGHT_SENSOR_MONO_DIAG_H
#define LIGHT_SENSOR_MONO_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "led_diag.h"
#include "light_sensor_types.h"

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_LIGHT_SENSOR
#error "+ HAS_LIGHT_SENSOR"
#endif

#ifndef HAS_LIGHT_SENSOR_MONO
#error "+ HAS_LIGHT_SENSOR_MONO"
#endif

#ifndef HAS_LIGHT_SENSOR_MONO_DIAG
#error "+ HAS_LIGHT_SENSOR_MONO_DIAG"
#endif

bool LedMonoDiag(LedHandle_t* const  LedNode);
bool LedMonoConfigDiag(const LedConfig_t*const  ConfigNode);

#endif /* LIGHT_SENSOR_MONO_DIAG_H  */
