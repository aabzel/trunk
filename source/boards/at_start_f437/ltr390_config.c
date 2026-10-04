#include "ltr390_config.h"

#include "data_utils.h"
#include "ltr390_types.h"

const Ltr390Config_t Ltr390Config[] = {
    {.num=1, .i2c_num=1, .valid=true, .name="Sun", .irq={.port=PORT_B, .pin=1,},},
};

Ltr390Handle_t Ltr390Instance[]={
    {.num=1, .valid=true, .init=false,}
};

const Ltr390Register_t Ltr390Register[]={
    {
            .address=LTR390_REG_ADDR_MEAS_RATE,
            .value.MeasRate={ .rate=LTR390_RATE_25_MS, .resolution=LTR390_RESOLUTION_CODE_20_BIT, },
    },

    {
            .address=LTR390_REG_ADDR_GAIN,      .value.AlsUvsGain={ .gain=LTR390_GAIN_CODE_18},
    },
};

uint32_t ltr390_reg_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(Ltr390Register);
    return cnt;
}


uint32_t ltr390_get_cnt(void){
    uint8_t cnt=0;
    cnt = ARRAY_SIZE(Ltr390Config);
    return cnt;
}

