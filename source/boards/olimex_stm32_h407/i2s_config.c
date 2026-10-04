#include "i2s_config.h"

#include "data_utils.h"
#include "i2s_const.h"
#include "i2s_isr.h"
#include "dma_channel_config.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif


static I2S_HandleTypeDef I2s2Handle = {0};
static I2S_HandleTypeDef I2s4Handle = {0};

#ifdef HAS_I2S4


static uint16_t I2s4TxSampleArray[I2S_MEM_SIZE] = {0};
static uint16_t I2s4RxSampleArray[I2S_MEM_SIZE] = {0};
#endif


#ifdef HAS_I2S5
static uint16_t I2s5TxSampleArray[I2S_MEM_SIZE] = {0};
static uint16_t I2s5RxSampleArray[I2S_MEM_SIZE] = {0};
#endif


#ifdef HAS_I2S_MCK
#define I2S2_COMMON_GPIO_MCK_VARIABLE                     \
    .GpioMClk = {.Pad = {.port = PORT_C, .pin = 6, },     \
                 .logic_level = GPIO_LVL_HI,              \
                 .name = " I2S2_MCK",                     \
                 .connector2 = "J2.15",                   \
                 .dir = GPIO_DIR_OUT,                     \
                 .speed = GPIO_SPEED_HIGH_SPEED,          \
                 .mode = GPIO_API_MODE_ALT1,              \
                 .pull = GPIO__PULL_DOWN,                 \
                 .mux = 5,                                \
              },

#else
#define I2S2_COMMON_GPIO_MCK_VARIABLE
#endif


#ifdef HAS_I2S_GPIO

#define I2S2_COMMON_GPIO_CLK_VARIABLE                   \
    .GpioSck= {.Pad = {.port = PORT_B, .pin = 13, },    \
               .logic_level = GPIO_LVL_HI,              \
               .name = " I2S2_CK",                      \
               .connector2 = "J3.10/J4.4",              \
               .dir = GPIO_DIR_OUT,                     \
               .speed=GPIO_SPEED_HIGH_SPEED,            \
               .mode = GPIO_API_MODE_ALT1,              \
               .pull = GPIO__PULL_DOWN,                  \
               .mux = 5,                                \
              },

#define I2S2_COMMON_GPIO_LR_CLK_VARIABLE                \
    .GpioLrCk={.Pad = {.port = PORT_B, .pin = 12,},     \
               .connector2 = "J3.11",                   \
               .mux = 5,                                \
               .dir = GPIO_DIR_OUT,                     \
               .name = "I2S2_WS",                       \
               .speed=GPIO_SPEED_HIGH_SPEED,            \
               .mode = GPIO_API_MODE_ALT1,              \
               .pull = GPIO__PULL_DOWN,                 \
               .logic_level = GPIO_LVL_HI,              \
             },

#define I2S2_COMMON_GPIO_IN_VARIABLE                    \
    .GpioSdIn = {.Pad = {.port = PORT_B, .pin = 15,},   \
              .connector2 = "J2.8",                     \
              .mux = 5,                                 \
              .dir = GPIO_DIR_IN,                       \
              .name = "I2S2_SDEXT(RX)",                 \
              .mode = GPIO_API_MODE_ALT1,               \
              .speed = GPIO_SPEED_HIGH_SPEED,           \
              .pull = GPIO__PULL_DOWN,                  \
              .logic_level = GPIO_LVL_HI,},             \

#define I2S2_COMMON_GPIO_OUT_VARIABLE                   \
    .GpioSdOut={.Pad = {.port=PORT_C, .pin=3},          \
               .connector2="J3.35",                     \
               .mux = 5,                                \
               .dir = GPIO_DIR_OUT,                     \
               .speed=GPIO_SPEED_HIGH_SPEED,            \
               .name="I2S2_SD(TX)",                     \
               .mode = GPIO_API_MODE_ALT1,              \
               .pull=GPIO__PULL_DOWN,                   \
               .logic_level=GPIO_LVL_HI,                \
    },


#define I2S2_COMMON_GPIO_VARIABLES                      \
    I2S2_COMMON_GPIO_LR_CLK_VARIABLE                    \
    I2S2_COMMON_GPIO_OUT_VARIABLE                       \
    I2S2_COMMON_GPIO_CLK_VARIABLE                       \
    I2S2_COMMON_GPIO_IN_VARIABLE                        \
    I2S2_COMMON_GPIO_MCK_VARIABLE                       \

#else
#define I2S2_COMMON_GPIO_VARIABLES
#endif


#ifdef HAS_I2S2

bool I2s2CallBackTxHalf(void) {
    bool res = false ;
    res = I2sDmaCallBackTxHalf(2);
    return res;
};

bool I2s2CallBackTxDone(void) {
    bool res = false ;
    res = I2sDmaCallBackTxDone(2);
    return res;
};

bool I2s2CallBackRxHalf(void) {
    bool res = false;
    res= I2sDmaCallBackRxHalf(2);
    return res;
};

bool I2s2CallBackRxDone(void) {
    bool res = false;
    res = I2sDmaCallBackRxDone(2);
    return res;
};

static uint16_t I2s2TxSampleArray[I2S_MEM_SIZE] = {0};
static uint16_t I2s2RxSampleArray[I2S_MEM_SIZE] = {0};

//        .dir_role = I2S_DIR_BUS_MODE_MASTER_TX,

#define I2S_CONFIG_I2S2_DMA                                           \
        .PadDmaRx =  { .port = PORT_A, .pin = 4, },                   \
        .PadDmaTx =  { .port = PORT_A, .pin = 8, },                   \
        .dma_channel_tx_num = DMA_CHANNEL_NUM_I2S2_TX,                \
        .dma_channel_rx_num = DMA_CHANNEL_NUM_I2S2_RX,                \
        .CallBackTxHalf = I2s2CallBackTxHalf ,                        \
        .CallBackTxDone = I2s2CallBackTxDone,                         \
        .CallBackRxHalf = I2s2CallBackRxHalf,                         \
        .CallBackRxDone = I2s2CallBackRxDone,

#define I2S_CONFIG_I2S2                                               \
    {                                                                 \
        .num = 2,                                                     \
        .need_init = true,                                            \
         I2S2_COMMON_GPIO_VARIABLES                                   \
         I2S_CONFIG_I2S2_DMA                                          \
        .bus_role = IF_BUS_ROLE_MASTER ,                              \
        .direction = CONNECT_DIR_TRANSMIT,                            \
        .led_tx_num = 1,                                              \
        .led_rx_num = 1,                                              \
        .sample_mode = SAMPLE_MODE_STEREO,                            \
        .audio_frequency_hz = AUDIO_FREQ_48K,                         \
        .data_format = I2S_DATA_FORMAT_16B,                           \
        .irq_priority = 0 ,                                           \
        .move_mode = MOVE_MODE_DMA ,                                  \
        .RxArray = I2s2RxSampleArray,                                 \
        .TxArray = I2s2TxSampleArray,                                 \
        .samples_cnt = ARRAY_SIZE(I2s2TxSampleArray),                 \
        .full_duplex = FULL_DUPLEX_ON,                                \
        .mclk_out = I2S_MCLKOUT_OFF,                                  \
        .standard = I2S_STD_PHILIPS,                                  \
        .cpol = I2S_CLOCK_POL_LOW,                                    \
        .clock_source = I2S_CLK_PLL,                                  \
        .name = "Play",                                               \
        .valid = true,                                                \
        .pHandle = &I2s2Handle,                                       \
    },

#else
#define I2S_CONFIG_I2S2
#endif

#ifdef HAS_I2S4
#define I2S4_COMMON_GPIO_OUT_VARIABLE I2S2_COMMON_GPIO_OUT_VARIABLE
#define I2S4_COMMON_GPIO_MCK_VARIABLE I2S2_COMMON_GPIO_MCK_VARIABLE
#define I2S4_COMMON_GPIO_CLK_VARIABLE I2S2_COMMON_GPIO_CLK_VARIABLE
#define I2S4_COMMON_GPIO_LR_CLK_VARIABLE I2S2_COMMON_GPIO_LR_CLK_VARIABLE

#define I2S4_COMMON_GPIO_IN_VARIABLE                    \
    .GpioSdIn = {.Pad = {.port = PORT_B, .pin = 15, },  \
              .connector2 = "J2.8",                     \
              .mux = 5,                                 \
              .dir = GPIO_DIR_IN,                       \
              .name = "I2S2_SDEXT(RX)",                 \
              .mode = GPIO_API_MODE_ALT1,               \
              .speed = GPIO_SPEED_HIGH_SPEED,           \
              .pull = GPIO__PULL_DOWN,                  \
              .logic_level = GPIO_LVL_HI,},

#define I2S4_COMMON_GPIO_VARIABLES                      \
        I2S4_COMMON_GPIO_OUT_VARIABLE                   \
        I2S4_COMMON_GPIO_IN_VARIABLE                    \
        I2S4_COMMON_GPIO_LR_CLK_VARIABLE                \
        I2S4_COMMON_GPIO_CLK_VARIABLE                   \
        I2S4_COMMON_GPIO_MCK_VARIABLE

#else
#define I2S4_COMMON_GPIO_VARIABLES
#endif

#ifdef HAS_I2S4
#define I2S_CONFIG_I2S4_DMA                                           \
        .PadDmaRx =  { .port = PORT_A, .pin = 4, },                   \
        .PadDmaTx =  { .port = PORT_A, .pin = 8, },                   \
        .dma_channel_tx_num = DMA_CHANNEL_NUM_I2S2_TX,                \
        .dma_channel_rx_num = DMA_CHANNEL_NUM_I2S2_RX,                \
        .CallBackRxHalf = I2s2CallBackRxHalf,                         \
        .CallBackRxDone = I2s2CallBackRxDone,                         \
        .CallBackTxHalf = I2s2CallBackTxHalf ,                        \
        .CallBackTxDone = I2s2CallBackTxDone,
#endif

#ifdef HAS_I2S4
#define I2S_CONFIG_I2S4                                 \
    {                                                   \
        .num = 4,                                       \
        .need_init = true,                              \
         I2S4_COMMON_GPIO_VARIABLES                     \
         I2S_CONFIG_I2S4_DMA                            \
        .bus_role = IF_BUS_ROLE_SLAVE,                  \
        .direction = CONNECT_DIR_RECEIVER,              \
        .led_tx_num = 1,                                \
        .led_rx_num = 1,                                \
        .sample_mode = SAMPLE_MODE_STEREO,              \
        .audio_frequency_hz = AUDIO_FREQ_48K,           \
        .data_format = I2S_DATA_FORMAT_16B,             \
        .irq_priority = 0 ,                             \
        .move_mode = MOVE_MODE_DMA ,                    \
        .RxArray = I2s4RxSampleArray,                   \
        .TxArray = I2s4TxSampleArray,                   \
        .samples_cnt = ARRAY_SIZE(I2s4TxSampleArray),   \
        .full_duplex = FULL_DUPLEX_OFF,                 \
        .mclk_out = I2S_MCLKOUT_OFF,                    \
        .standard = I2S_STD_PHILIPS,                    \
        .cpol = I2S_CLOCK_POL_LOW,                      \
        .clock_source = I2S_CLK_PLL,                    \
        .name = "rec",                              \
        .valid = true,                                  \
        .pHandle = &I2s4Handle,                         \
    },
#else
#define I2S_CONFIG_I2S4
#endif

/*constant compile-time known settings*/
const I2sConfig_t I2sConfig[] = {
        I2S_CONFIG_I2S2
        I2S_CONFIG_I2S4
#ifdef HAS_I2S1
    {
        .num = 1,
        .full_duplex = FULL_DUPLEX_OFF,
        .mode = I2SMODE_MASTER_TX,
        .data_format = I2S_DATA_FORMAT_32B,
        .audio_freq = AUDIO_FREQ_44K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S1",
        .ParamId.bus_role = PAR_ID_I2S4_BUS_ROLE,
        .valid=true,
    },
#endif


#ifdef HAS_I2S3
    {
        .num = 3,
        .full_duplex = FULL_DUPLEX_ON,
        .mode = I2SMODE_MASTER_RX,
        .data_format = I2S_DATA_FORMAT_16B,
        .audio_freq = AUDIO_FREQ_32K,
        .mclk_out = I2S_MCLKOUT_OFF,
        .standard = I2S_STD_PHILIPS,
        .cpol = I2S_CLOCK_POL_LOW,
        .clock_source = I2S_CLK_PLL,
        .name = "I2S3",
        .ParamId.bus_role = PAR_ID_I2S3_BUS_ROLE,
        .valid=true,
    },
#endif
};

I2sHandle_t I2sInstance[] = {
#ifdef HAS_I2S1
    {        .num = 1,         .valid=true,    },
#endif

#ifdef HAS_I2S2
    {        .num = 2,        .valid=true,    },
#endif

#ifdef HAS_I2S3
    {        .num = 3,        .valid=true,    },
#endif

#ifdef HAS_I2S4
    {        .num = 4,        .valid=true,    },
#endif

#ifdef HAS_I2S5
    {        .num = 5,        .valid=true,    },
#endif

};

COMPONENT_GET_CNT(I2s, i2s)

bool I2s4CallBackTxHalf(void){
    bool res = false ;
    return res;
}


bool I2s4CallBackTxDone(void){
    bool res = false ;
    return res;
}
