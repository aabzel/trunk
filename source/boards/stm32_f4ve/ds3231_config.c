#include "ds3231_config.h"

#ifdef HAS_I2C
#include "i2c_drv.h"
#endif

#include "data_utils.h"
#include "ds3231_types.h"

const Ds3231Config_t Ds3231Config[]={
    {.num=1, .i2c_num=1, .valid=true, .hour_mode=HOUR_MODE_24H, .offset=127, .rate_select=RS_8192_HZ,},
};

Ds3231Handle_t Ds3231Item[]={
    {.num=1, .valid=true, .init=false,}
};

const Ds3231RegConfig_t Ds3231RegConfig[]={
};

uint32_t ds3231_get_reg_config_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(Ds3231RegConfig);
    return cnt;
}


uint32_t ds3231_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(Ds3231Config);
    return cnt;
}

