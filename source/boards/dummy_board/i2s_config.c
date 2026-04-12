#include "i2s_config.h"

#ifdef HAS_COMPLEX
#include <complex.h>
#endif
#include <stddef.h>

#include "data_utils.h"
#include "i2s_const.h"
#ifdef HAS_PARAM
#include "param_constants.h"
#endif

//#include "c_defines_generated.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif /**/

#ifdef HAS_DFT
static double complex DftMem[I2S_BUFFER_SIZE / 2];
#endif /*HAS_DFT*/

/*constant compile-time known settings*/
const I2sConfig_t I2sConfig[] = {
#ifdef HAS_I2S1
    {
        .Dma =
            {
                .dma_num = 3,
                .channel = 63,
            },
#ifdef HAS_DFT
        .dft_mem = DftMem,
#endif /*HAS_DFT*/
        .num = 1,
        .mode = I2S_MODE_INTERRUPT,
        .valid = true,
        .full_duplex = FULL_DUPLEX_OFF,
        //.bus_role = I2SMODE_MASTER_TX,
        .bus_role = IF_BUS_ROLE_MASTER,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq_hz = I2S_AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S1",
        .sample_mode = SAMPLE_MODE_STEREO,
#ifdef HAS_PARAM
        .ParamId.bus_role = PAR_ID_I2S1_BUS_ROLE,
#endif
    },
#endif /*HAS_I2S1*/

#ifdef HAS_I2S2
    {
        .PadDebug1 =
            {
                .port = PORT_B,
                .pin = 0,
            },
        .PadDebug2 =
            {
                .port = PORT_B,
                .pin = 1,
            },
#ifdef HAS_I2S_DMA
        .Dma =
            {
                .dma_num = 1,
                .channel = 1,
            },
#endif
        .GpioSdIn = {.pad = {.port = PORT_C, .pin = 2},
                     .mux = 6,
                     .dir = GPIO_DIR_IN,
                     .name = "I2S2_SDEXT",
                     .mode = GPIO_API_MODE_ALT1,
                     .pull = GPIO__PULL_UP,
                     .logic_level = GPIO_LVL_HI},
        .GpioSdOut = {.pad = {.port = PORT_C, .pin = 3},
                      .mux = 5,
                      .dir = GPIO_DIR_OUT,
                      .name = "I2S2_SDout",
                      .mode = GPIO_API_MODE_ALT1,
                      .pull = GPIO__PULL_UP,
                      .logic_level = GPIO_LVL_HI},
        .GpioSck = {.pad = {.port = PORT_C, .pin = 7},
                    .mux = 5,
                    .dir = GPIO_DIR_OUT,
                    .name = "I2S2_CK",
                    .mode = GPIO_API_MODE_ALT1,
                    .pull = GPIO__PULL_DOWN,
                    .logic_level = GPIO_LVL_HI},
        .GpioLrCk = {.pad = {.port = PORT_B, .pin = 9},
                     .mux = 5,
                     .dir = GPIO_DIR_OUT,
                     .name = "I2S2_WS",
                     .mode = GPIO_API_MODE_ALT1,
                     .pull = GPIO__PULL_UP,
                     .logic_level = GPIO_LVL_HI},

        .valid = true,
#ifdef HAS_DFT
        .dft_mem = DftMem,
#endif /*HAS_DFT*/
        .num = 2,
        .bus_role = IF_BUS_ROLE_SLAVE,
        .direction = CONNECT_DIR_RECEIVER,
        .mode = I2S_MODE_INTERRUPT,

        .samples_cnt = I2S_BUFFER_SIZE,
        .irq_priority = 5,
        .full_duplex = FULL_DUPLEX_OFF,
        .bus_role = IF_BUS_ROLE_MASTER,
        .data_format = I2S_DATA_FORMAT_16B_EXTENDED,
        .audio_freq_hz = I2S_AUDIO_FREQ_48K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .sample_mode = SAMPLE_MODE_STEREO,
        .name = "I2S2",
#ifdef HAS_PARAM
        .ParamId.bus_role = PAR_ID_I2S2_BUS_ROLE,
#endif /*HAS_PARAM*/
    },
#endif /*HAS_I2S2*/

#ifdef HAS_I2S3
    {
#ifdef HAS_I2S_DMA
        .Dma =
            {
                .dma_num = 1,
                .channel = 3,
            },
#endif
            .GpioLrCk =  {
                    .pad={.port=PORT_A, .pin=4},
                    .connector2="PA4,J2.40",
                    .mux=6,
                    .dir=GPIO_DIR_OUT,
                    .name="I2S3_WS",
                    .mode=GPIO_API_MODE_ALT1,
                    .pull=GPIO__PULL_UP,
                    .logic_level=GPIO_LVL_HI,
        },
            .GpioSck = {
                    .pad={.port=PORT_C, .pin=10},
                    .connector2="PC10,J1.39",
                    .mux=6,
                    .dir=GPIO_DIR_OUT,
                    .name="I2S3_CK",
                    .mode=GPIO_API_MODE_ALT1,
                    .pull=GPIO__PULL_DOWN,
                    .logic_level=GPIO_LVL_HI,
        },
            .GpioSdOut =  {
                    .pad={.port=PORT_B, .pin=0},
                    .connector2="PB0,J2.46",
                    .mux=7,
                    .dir=GPIO_DIR_OUT,
                    .name="I2S3_SD",
                    .mode=GPIO_API_MODE_ALT1,
                    .pull=GPIO__PULL_UP,
                    .logic_level=GPIO_LVL_HI,
        },
            .GpioSdIn =  {
                    .pad={.port=PORT_C, .pin=11},
                    .connector2="PC11,J1.40",
                    .mux=5,
                    .dir=GPIO_DIR_OUT,
                    .name="I2S3_SDEXT",
                    .mode=GPIO_API_MODE_ALT1,
                    .pull=GPIO__PULL_UP,
                    .logic_level=GPIO_LVL_HI,
        },


#ifdef HAS_DFT
        .dft_mem = DftMem,
#endif /*HAS_DFT*/
#ifdef HAS_PARAM
        .ParamId.bus_role = PAR_ID_I2S3_BUS_ROLE,
#endif
        .num = 3,
        .bus_role = IF_BUS_ROLE_MASTER,
        .direction = CONNECT_DIR_TRANSMITTER,
        .mode = I2S_MODE_INTERRUPT,

        .audio_freq_hz = I2S_AUDIO_FREQ_48K,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .data_format = I2S_DATA_FORMAT_32B,
        .full_duplex = FULL_DUPLEX_OFF,
        .mclk_out = I2S_MCLKOUT_OFF,
        .name = "I2S3",
        .standard = I2S_STD_PHILIPS,
        .sample_mode = SAMPLE_MODE_STEREO,
        .valid = true,
    },
#endif /*HAS_I2S3*/

#ifdef HAS_I2S4
    {
        .Dma =
            {
                .dma_num = 3,
                .channel = 63,
            },
        .mode = I2S_MODE_INTERRUPT,
        .num = 4,
        .valid = true,
#ifdef HAS_DFT
        .dft_mem = DftMem,
#endif /*HAS_DFT*/
        .full_duplex = FULL_DUPLEX_OFF,
        //.bus_role = I2SMODE_MASTER_TX,
        .bus_role = IF_BUS_ROLE_MASTER,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq_hz = I2S_AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .sample_mode = SAMPLE_MODE_STEREO,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S4",

#ifdef HAS_PARAM
        .ParamId.bus_role = PAR_ID_I2S4_BUS_ROLE,
#endif
    },
#endif /*HAS_I2S4*/

#ifdef HAS_I2S5
    {
#ifdef HAS_I2S_DMA
        .Dma =
            {
                .dma_num = 1,
                .channel = 2,
            },
#endif
        .valid = true,
        .GpioSdIn = {.pad = {.port = PORT_C, .pin = 2},
                     .mux = 6,
                     .dir = GPIO_DIR_IN,
                     .name = "I2S2_SDin",
                     .mode = GPIO_API_MODE_ALT1,
                     .pull = GPIO__PULL_UP,
                     .logic_level = GPIO_LVL_HI},
        .GpioSdOut = {.pad = {.port = PORT_C, .pin = 3},
                      .mux = 5,
                      .dir = GPIO_DIR_OUT,
                      .name = "I2S2_SDout",
                      .mode = GPIO_API_MODE_ALT1,
                      .pull = GPIO__PULL_UP,
                      .logic_level = GPIO_LVL_HI},
        .GpioSck = {.pad = {.port = PORT_C, .pin = 7},
                    .mux = 5,
                    .dir = GPIO_DIR_OUT,
                    .name = "I2S2_CK",
                    .mode = GPIO_API_MODE_ALT1,
                    .pull = GPIO__PULL_AIR,
                    .logic_level = GPIO_LVL_HI},
        .GpioLrCk = {.pad = {.port = PORT_B, .pin = 9},
                     .mux = 5,
                     .dir = GPIO_DIR_OUT,
                     .name = "I2S2_WS",
                     .mode = GPIO_API_MODE_ALT1,
                     .pull = GPIO__PULL_AIR,
                     .logic_level = GPIO_LVL_HI},
        .audio_freq_hz = I2S_AUDIO_FREQ_48K,
        //.bus_role = I2SMODE_SLAVE_RX, /* see 13.3.2 I2S full-duplex*/
        .num = 5,
        .bus_role = IF_BUS_ROLE_SLAVE,
        .direction = CONNECT_DIR_RECEIVER,

        .clock_source = I2S_CLK_PLL,
        .cpol = I2S_CLOCK_POL_LOW,
        .data_format = I2S_DATA_FORMAT_16B_EXTENDED,
#ifdef HAS_DFT
        .dft_mem = DftMem,
#endif /*HAS_DFT*/
        .full_duplex = FULL_DUPLEX_OFF,
        .name = "I2S2EXT",
        .mode = I2S_MODE_DMA,
        .mclk_out = I2S_MCLKOUT_OFF,
#ifdef HAS_PARAM
        .ParamId.bus_role = PAR_ID_I2S2_BUS_ROLE,
#endif
        .sample_mode = SAMPLE_MODE_STEREO,
        .samples_cnt = I2S_BUFFER_SIZE,
        .standard = I2S_STD_PHILIPS,
    },
#endif /*HAS_I2S5*/

};

I2sHandle_t I2sInstance[] = {
#ifdef HAS_I2S1
    {
        .num = 1,
        .valid = true,
    },
#endif

#ifdef HAS_I2S2
    {
        .num = 2,
        .valid = true,
    },
#endif

#ifdef HAS_I2S3
    {
        .num = 3,
        .valid = true,
    },
#endif

#ifdef HAS_I2S4
    {
        .num = 4,
        .valid = true,
    },
#endif

#ifdef HAS_I2S5
    {
        .num = 5,
        .valid = true,
    },
#endif

#ifdef HAS_I2S6
    {
        .num = 6,
        .valid = true,
    },
#endif
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
