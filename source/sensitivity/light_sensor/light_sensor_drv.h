#ifndef LIGHT_SENSOR_DRIVER_H
#define LIGHT_SENSOR_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "led_config.h"
#include "light_sensor_types.h"
#include "light_sensor_config.h"

#ifndef HAS_LIGHT_SENSOR
#error "+ HAS_LIGHT_SENSOR"
#endif

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

double light_sensor_read(uint32_t num);
bool light_sensor_init(void);

const LightSensorConfig_t* LightSensorGetConfig(uint8_t lx_num);
LightSensorHandle_t* LightSensorGetNode(uint8_t lx_num);


#endif /* LIGHT_SENSOR_DRIVER_H  */
