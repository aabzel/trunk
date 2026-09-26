#ifndef LIGHT_SENSOR_TYPES_H
#define LIGHT_SENSOR_TYPES_H

#include "std_includes.h"
#include "light_sensor_const.h"

#define LIGHT_SENSOR_GENERAL_VARIABLES  \
    bool valid;                         \
    uint8_t num;                        \
    char* name;                         \
    LightSensor_t sen_type;             \
    uint8_t sen_num;

typedef struct  {
    LIGHT_SENSOR_GENERAL_VARIABLES
} LightSensorConfig_t;

typedef struct  {
    LIGHT_SENSOR_GENERAL_VARIABLES
    bool init;
} LightSensorHandle_t;

#endif /* LIGHT_SENSOR_TYPES_H  */
