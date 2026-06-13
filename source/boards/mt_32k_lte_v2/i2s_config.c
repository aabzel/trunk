#include "i2s_config.h"

#include "data_utils.h"
#include "i2s_const.h"
#include "param_constants.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif /**/

/*constant compile-time known settings*/
const I2sConfig_t I2sConfigLuT[] = {
#ifdef HAS_I2S1
    {
        .num = 1,
        .full_duplex = FULL_DUPLEX_OFF,
        .mode = I2SMODE_MASTER_TX,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq = I2S_AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S1",
        .ParamId.bus_role = PAR_ID_I2S4_BUS_ROLE,
        .valid=true,
    },
#endif /**/
#ifdef HAS_I2S2
    {
        .num = 2,
        .full_duplex = FULL_DUPLEX_OFF,
        .mode = I2SMODE_MASTER_TX,
        .data_format = I2S_DATA_FORMAT_16B,
        .audio_freq = I2S_AUDIO_FREQ_48K,
        .mclk_out = I2S_MCLKOUT_ON,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S2",
        .ParamId.bus_role = PAR_ID_I2S2_BUS_ROLE,
		.valid=true,
    },
#endif /**/
#ifdef HAS_I2S3
    {
        .num = 3,
        .full_duplex = FULL_DUPLEX_ON,
        .mode = I2SMODE_MASTER_RX,
        .data_format = I2S_DATA_FORMAT_16B,
        .audio_freq = I2S_AUDIO_FREQ_32K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S3",
        .ParamId.bus_role = PAR_ID_I2S3_BUS_ROLE,
		.valid=true,
    },
#endif /**/
};

/*TODO: Move I2sConfig to Stack*/
I2sConfig_t I2sConfig[3];

I2sHandle_t I2sInstance[] = {
#ifdef HAS_I2S1
    {
        .num = 1,
        .rx_buff = NULL,
        .rx_buff_size = 0,
		.valid=true,
    },
#endif
#ifdef HAS_I2S2
    {
        .num = 2,
        .rx_buff = NULL,
        .rx_buff_size = 0,
		.valid=true,
    },
#endif
#ifdef HAS_I2S3
    {
        .num = 3,
        .rx_buff = NULL,
        .rx_buff_size = 0,
		.valid=true,
    },
#endif
};

uint32_t i2s_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2sConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(I2sInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
