#ifndef LIGHT_SENSOR_DRIVER_H
#define LIGHT_SENSOR_DRIVER_H

#include "std_includes.h"
#include "led_config.h"
#include "light_sensor_types.h"
#include "light_sensor_config.h"

double light_sensor_read(uint32_t num);
bool light_sensor_init(void);

const LightSensorConfig_t* LightSensorGetConfig(uint8_t lx_num);
LightSensorHandle_t* LightSensorGetNode(uint8_t lx_num);


#endif /* LIGHT_SENSOR_DRIVER_H  */
