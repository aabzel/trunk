#include "accelerometer_config.h"

#include "data_utils.h"

const AccelerometerConfig_t AccelerometerConfig[ ] = {
    {.num=1, .accel_phy=ACCEL_PHY_LIS3DH, .accel_num=1,  .name="LIS3DH", .valid=true,},
};

AccelerometerHandle_t AccelerometerInstance[ ]={
    {.num=1, .valid=true,},
};

uint32_t accelerometer_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(AccelerometerInstance);
    cnt2 = ARRAY_SIZE(AccelerometerConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
