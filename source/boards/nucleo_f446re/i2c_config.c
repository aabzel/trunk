#include "i2c_config.h"

#include "data_utils.h"

/*constant compile-time known settings*/
const I2cConfig_t I2cConfig[] = {
#ifdef HAS_I2C1
    { .num=1, .clock_speed=100000, .name = "I2C1", .valid=true,},
#endif

#ifdef HAS_I2C2
    { .num=2, .clock_speed=100000, .name = "I2C2", .valid=true,},
#endif

#ifdef HAS_I2C3
    { .num=3, .clock_speed=100000, .name = "I2C3", .valid=true,},
#endif

#ifdef HAS_I2C4
    { .num=4, .clock_speed=100000, .name = "I2C4", .valid=true,},
#endif
};

I2cHandle_t I2cInstance[]={
#ifdef HAS_I2C1
    {.num=1, .valid=true, },
#endif

#ifdef HAS_I2C2
   {.num=2, .valid=true, },
#endif

#ifdef HAS_I2C3
    {.num=3,  .valid=true,},
#endif

#ifdef HAS_I2C4
    {.num=4,  .valid=true,},
#endif
};

uint32_t i2c_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2cConfig);
    uint32_t cnt_ints = ARRAY_SIZE(I2cInstance);
    if(cnt_conf == cnt_ints){
        cnt = cnt_ints;
    }
    return cnt;
}

