#include "light_sensor_config.h"

#include "data_utils.h"

const LightSensorConfig_t LightSensorConfig[ ] = {
   {.num=1, .sen_type=LI_SENS_PHOTORESISTOR, .sen_num=1,  .name="PhotoResistor", .valid=true,},
   {.num=2, .sen_type=LI_SENS_BH1750, .sen_num=1,  .name="BH1750", .valid=true,},
};

LightSensorHandle_t LightSensorItem[ ]={
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
};

uint32_t light_sensor_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LightSensorItem);
    cnt2 = ARRAY_SIZE(LightSensorConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
