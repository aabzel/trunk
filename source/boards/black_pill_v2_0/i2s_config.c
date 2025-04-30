#include "i2s_config.h"

#include "data_utils.h"
#include "i2s_const.h"
#include "param_constants.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif /**/

/*constant compile-time known settings*/
const I2sConfig_t I2sConfigLuT[] = {
#ifdef HAS_FDA801
    {
        .num = I2S_FDA801,
        .full_duplex = FULL_DUPLEX_OFF,
        .mode = I2SMODE_MASTER_TX,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq = I2S_AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "FDA801",
        .ParamId.bus_role = PAR_ID_I2S4_BUS_ROLE,
    },
#endif /**/
#ifdef HAS_BC127
    {
        .num = I2S_BC127,
        .full_duplex = FULL_DUPLEX_OFF,
        .mode = I2SMODE_MASTER_RX,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq = I2S_AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "BC127",
        .ParamId.bus_role = PAR_ID_I2S1_BUS_ROLE,
    },
#endif /**/
#ifdef HAS_WM8731
    {
        .num = I2S_WM8731,
        .full_duplex = FULL_DUPLEX_ON,
        .mode = I2SMODE_MASTER_RX,
        .data_format = I2S_DATA_FORMAT_16B,
        .audio_freq = I2S_AUDIO_FREQ_32K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "WM8731",
        .ParamId.bus_role = PAR_ID_I2S2_BUS_ROLE,
    },
#endif /**/
};

/*TODO: Move I2sConfig to Stack*/
I2sConfig_t I2sConfig[3];

I2sHandle_t I2sInstance[] = {
#ifdef HAS_BC127
    {
        .num = I2S_BC127,
        .rx_buff = NULL,
        .rx_buff_size = 0,
    },
#endif
#ifdef HAS_WM8731
    {
        .num = I2S_WM8731,
        .rx_buff = NULL,
        .rx_buff_size = 0,
    },
#endif
#ifdef HAS_FDA801
    {
        .num = I2S_FDA801,
        .rx_buff = NULL,
        .rx_buff_size = 0,
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
