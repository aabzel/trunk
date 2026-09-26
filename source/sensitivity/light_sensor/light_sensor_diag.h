#ifndef LIGHT_SENSOR_MONO_DIAG_H
#define LIGHT_SENSOR_MONO_DIAG_H

#include "std_includes.h"
#include "light_sensor_types.h"

#ifndef HAS_LIGHT_SENSOR
#error "+ HAS_LIGHT_SENSOR"
#endif

bool LightSensorDiag(LightSensorHandle_t* const  LightSensorNode);
bool LightSensorConfigDiag(const LightSensorConfig_t*const  ConfigNode);

#endif /* LIGHT_SENSOR_MONO_DIAG_H  */
