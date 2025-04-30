#include "bh1750_config.h"

#include "data_utils.h"
#include "bh1750_types.h"

const Bh1750Config_t Bh1750Config[] = {
    {.num=1, .i2c_num=3, .chip_addr=BH1750_I2C_ADDR_0, .valid=true, .name="Sun",},
};

Bh1750Handle_t Bh1750Instance[]={
    {.num=1, .valid=true, .init=false,}
};

uint32_t bh1750_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(Bh1750Config);
    return cnt;
}

