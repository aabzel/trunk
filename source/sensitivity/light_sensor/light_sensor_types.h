#ifndef LIGHT_SENSOR_TYPES_H
#define LIGHT_SENSOR_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "light_sensor_const.h"

#define LIGHT_SENSOR_GENERAL_VARIABLES  \
    bool valid;                         \
    uint8_t num;                        \
    LightSensor_t sen_type;             \
    uint8_t sen_num;

typedef struct  {
    LIGHT_SENSOR_GENERAL_VARIABLES
    char name[LIGHT_SENSOR_NAME_SIZE];
} LightSensorConfig_t;

typedef struct  {
    LIGHT_SENSOR_GENERAL_VARIABLES
    bool init;
} LightSensorHandle_t;

#endif /* LIGHT_SENSOR_TYPES_H  */
