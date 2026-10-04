#include "light_sensor_config.h"

#include "data_utils.h"

const LightSensorConfig_t SECTION_CFG_DATA LightSensorConfig[ ] = {
   {.num=1, .sen_type=LI_SENS_PHOTORESISTOR, .sen_num=1,  .name="PhotoResistor", .valid=true,},
   {.num=2, .sen_type=LI_SENS_BH1750, .sen_num=1,  .name="BH1750", .valid=true,},
};

LightSensorHandle_t LightSensorItem[ ]={
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
};

COMPONENT_GET_CNT(LightSensor, light_sensor)

