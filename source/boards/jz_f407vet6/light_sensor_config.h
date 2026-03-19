#ifndef LIGHT_SENSOR_CONFIG_H
#define LIGHT_SENSOR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "light_sensor_types.h"

extern const LightSensorConfig_t LightSensorConfig[ ];
extern LightSensorHandle_t LightSensorItem[ ];

uint32_t light_sensor_get_cnt(void);

#endif /* LIGHT_SENSOR_CONFIG_H  */
