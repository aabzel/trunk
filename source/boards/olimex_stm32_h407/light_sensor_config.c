#include "light_sensor_config.h"

#include "data_utils.h"

const LightSensorConfig_t LightSensorConfig[ ] = {
    {.num = 1, .sen_type = LI_SENS_LTR390_UVS, .sen_num = 1,  .name = "LTR390_UVS", .valid = true,},
    {.num = 2, .sen_type = LI_SENS_LTR390_ALS, .sen_num = 1,  .name = "LTR390_ALS", .valid = true,},
};

LightSensorHandle_t LightSensorItem[ ] = {
    {.num = 1, .valid = true, },
    {.num = 2, .valid = true, },
};

COMPONENT_GET_CNT(LightSensor, light_sensor)

