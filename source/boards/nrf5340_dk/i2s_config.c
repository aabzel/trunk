#include "i2s_config.h"

#ifdef HAS_COMPLEX
#include <complex.h>
#endif
#include <stddef.h>

#include "audio_types.h"
#include "data_utils.h"
#include "i2s_const.h"

#ifdef HAS_I2S_LEGACY
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

#define I2S_SAMPLE_RATE 48000
#define I2S_CHANNEL_BIT 32
#define I2S_SAMPLES_CNT_0_5_S ((I2S_SAMPLE_RATE * 2) / 2)
#define I2S_SAMPLES_CNT_0_25_S ((I2S_SAMPLE_RATE * 2) / 4)
#define I2S_SAMPLES_CNT_0_125_S ((I2S_SAMPLE_RATE * 2) / 8)
#define I2S_SAMPLES_CNT_62_MS ((I2S_SAMPLE_RATE * 2) / 16)
#define I2S_FRAME_CNT_DEFAULT (I2S_SAMPLES_CNT_62_MS)

// static SampleType_t rx_buf[I2S_FRAME_CNT_DEFAULT];
#ifdef HAS_DFT
static double complex DftMem[I2S_FRAME_CNT_DEFAULT];
#endif /*HAS_DFT*/

/*constant compile-time known settings*/
const I2sConfig_t I2sConfigLuT[1] = {{
    .num = 0,
    .audio_freq = I2S_AUDIO_FREQ_48K,
    .sample_mode = SAMPLE_MODE_MONO,
    .full_duplex = FULL_DUPLEX_ON,
    .samples_cnt = I2S_BUFFER_SIZE, /*TxSampleCnt*/
//.rx_buffer = rx_buf, /*RxBuff*/
#ifdef HAS_DFT
    .dft_mem = DftMem, /**/
#endif
    .debug_led1_num = 1,
    .debug_led2_num = 1,
#ifdef HAS_I2S0_SLAVE
    .mode = I2SMODE_SLAVE,
#endif /*HAS_I2S_SLAVE*/

#ifdef HAS_I2S0_MASTER
    .mode = I2SMODE_MASTER,
#endif /*HAS_I2S_MASTER*/

#ifdef HAS_I2S_LEGACY
    .data_format = I2S_DATA_FORMAT_16B,
#else
    //.data_format = I2S_DATA_FORMAT_32B,
    .data_format = I2S_DATA_FORMAT_16B,
#endif
    .mclk_out = I2S_MCLKOUT_OFF,
    .clock_source = I2S_CLK_PLL,
    .name = "AudioDAC",
    .sck_freq_hz = 64 * I2S_AUDIO_FREQ_48K, // MHZ_2_HZ(3.2),
    //.sck_freq_hz = 348*I2S_AUDIO_FREQ_48K,//MHZ_2_HZ(3.2),
    .PadSck =
        {
            .port = 0,
            .pin = 6,
        },
    .PadLrCk =
        {
            .port = 0,
            .pin = 7,
        },
    .PadSdOut =
        {
            .port = 0,
            .pin = 25,
        },
    .PadSdIn =
        {
            .port = 1,
            .pin = 4,
        },
#if 0
    .PadMClk =
        {
            .port = 1,
            .pin = 5,
        },
#else
    .PadMClk =
        {
            .port = 2,
            .pin = 31,
        },
#endif
    .valid = true,

#ifdef HAS_I2S_ISR
#ifdef HAS_I2S_LEGACY
    //.I2sIsrHandler = i2s_comp_handler,
    .I2sIsrHandler = NULL,
#else  /*HAS_I2S_LEGACY*/
    .I2sIsrHandler = NrfxI2s0DataHandler,
#endif /*HAS_I2S_LEGACY*/
#else  /*HAS_I2S_ISR*/
    .I2sIsrHandler = NULL,
#endif /*HAS_I2S_ISR*/
}};

I2sHandle_t I2sInstance[1] = {{
    .num = 0,
    .valid = true,
}};

uint32_t i2s_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_conf = ARRAY_SIZE(I2sConfigLuT);
    uint32_t cnt_ints = ARRAY_SIZE(I2sInstance);
    if(cnt_conf == cnt_ints) {
        cnt = cnt_ints;
    }
    return cnt;
}
