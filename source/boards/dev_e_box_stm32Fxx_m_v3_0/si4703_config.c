#include "si4703_config.h"

#include "data_utils.h"

const Si4703Config_t Si4703Config[]  =  {
    {
        .num  =  1,
        .valid  =  true,
        .name  =  "SI4703",
        .i2c_num  =  1,
        .i2c_addr  =  SI4703_I2C_ADDR,
        .rds_en =  false,
        .rds_int_fifo_cnt = 1,
        .PadSclk = {.port = PORT_B,  .pin = 8, },
        .PadSdio = {.port = PORT_B,  .pin = 9, },
        .PadReset = {.port = PORT_A, .pin = 1, },
        .PadSen = {.port = PORT_A,   .pin = 4, },
        .PadGpio1 = {.port = PORT_A, .pin = 8, },
        .PadGpio2 = {.port = PORT_A, .pin = 11,},

        .SysCfg1 = {
            .gpio1 = 0,
            .gpio2 = 1,
            .gpio3 = 0,
            .blndadj = 0,
            .res = 0,
            .agcd = 0,
            .de = 1,
            .rds = RDS_ENABLE,
            .res2 = 0,
            .stcien = 1,
            .rdsien = RDS_INT_ENABLE,
        },

        .SysCfg2 = {
            .seekth  =  0,/**/
            .band = BAND_SEL_87_5_108_MHz,/**/
            .space = CHAN_SPACE_100_KHZ,/**/
            .volume = 1,/**/
        },
        .SysCfg3 = {
           .smuter =  0, /*Softmute Attack/Recover Rate*/
           .smutea  = 0, /*Softmute Attenuation*/
           .res = 0 ,    /**/
           .volext =  0, /*Extended Volume Range*/
           .sksnr  =  0, /*Seek SNR Threshold*/
           .skcnt  = 0,  /*Seek FM Impulse Detection Threshold.*/
        }
    },
};

Si4703Handle_t Si4703Instance[]  =  {
    { .num  =  1, .valid  =  true, },
};

uint32_t si4703_get_cnt(void) {
    uint8_t cnt1  =  0;
    uint8_t cnt2  =  0;
    cnt1  =  ARRAY_SIZE(Si4703Config);
    cnt2  =  ARRAY_SIZE(Si4703Instance);
    if(cnt2  ==  cnt1) {
    }
    return cnt1;
}
