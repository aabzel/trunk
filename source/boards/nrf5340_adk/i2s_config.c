#include "i2s_config.h"

#include  <stddef.h>

#include "data_utils.h"
#include "i2s_const.h"

#ifdef HAS_LEGACY_I2S
#include "audio_i2s.h"
#endif

#ifdef HAS_CLOCK
#include "clock_utils.h"
#endif /*HAS_CLOCK*/

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif /*HAS_I2S*/

#ifdef HAS_I2S_ISR
#include "i2s_isr.h"
#endif

#if !defined(HAS_I2S0_SLAVE) && !defined(HAS_I2S0_MASTER)
#error "some I2S0 role must be defined"
#endif

/*constant compile-time known settings*/
const I2sConfig_t I2sConfig[1] = {
    {
        .num = 0,
        .full_duplex = FULL_DUPLEX_ON,
#ifdef HAS_I2S0_SLAVE
        .mode = I2SMODE_SLAVE,
#endif /*HAS_I2S_SLAVE*/

#ifdef HAS_I2S0_MASTER
        .mode = I2SMODE_MASTER,
#endif /*HAS_I2S_MASTER*/

#ifdef HAS_LEGACY_I2S
        .data_format = I2S_DATA_FORMAT_16B,
#else
        .data_format = I2S_DATA_FORMAT_32B,
#endif
        .audio_freq = I2S_AUDIO_FREQ_48K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .clock_source = I2S_CLK_PLL,
        .name = "AudioDAC",
        .sck_freq_hz = 64*I2S_AUDIO_FREQ_48K,//MHZ_2_HZ(3.2),
        //.sck_freq_hz = 348*I2S_AUDIO_FREQ_48K,//MHZ_2_HZ(3.2),
        .PadSck.port=0,   .PadSck.pin=6,
        .PadLrCk.port=0,  .PadLrCk.pin=7,
        .PadSdOut.port=0, .PadSdOut.pin=25,
        .PadSdIn.port=1,  .PadSdIn.pin=4,
        .PadMClk.port=1,  .PadMClk.pin=5,
        .valid=true,
#ifdef HAS_LEGACY_I2S
		.I2sIsrHandler=i2s_comp_handler,
#else
		.I2sIsrHandler=NrfxI2s0DataHandler,
#endif
    }
};

I2sHandle_t I2sInstance[1] = {
    {
        .num = 0,
        .rx_buff = NULL,
        .rx_buff_size = 0,
        .valid= true,
    }
};

uint32_t i2s_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2sConfig);
    uint32_t cnt_ints = ARRAY_SIZE(I2sInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
