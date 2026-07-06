#include "i2s_config.h"

#include "data_utils.h"
#include "i2s_const.h"
#include "i2s_isr.h"
#include "dma_channel_config.h"

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif

#ifdef HAS_I2S_GPIO
#define I2S2_COMMON_GPIO_VARIABLES             \
        .PadDebug1 = { .port=PORT_?, .pin=?, },                                           \
        .PadDebug2 = { .port=PORT_?, .pin=?, },                                           \
    .GpioSdIn={.pad = {.port=PORT_C, .pin=2,},  \
              .connector2="J3.36",             \
              .mux = 6,                        \
              .dir=GPIO_DIR_IN,                \
              .name="I2S2_SDEXT",              \
              .mode = GPIO_API_MODE_ALT1,      \
              .pull = GPIO__PULL_UP,           \
              .logic_level = GPIO_LVL_HI,},    \
    .GpioSck= {.pad = {.port=PORT_B, .pin=10,}, \
              .connector2="J3.13",             \
              .mux = 5, .dir=GPIO_DIR_OUT,     \
              .name="I2S2_CK",                 \
              .mode = GPIO_API_MODE_ALT1,      \
              .pull=GPIO__PULL_DOWN,           \
              .logic_level=GPIO_LVL_HI,},      \
    .GpioLrCk={.pad = {.port=PORT_B, .pin=12,}, \
               .connector2="J3.11",            \
              .mux = 5,                        \
              .dir=GPIO_DIR_OUT, \
              .name="I2S2_WS",    \
              .mode = GPIO_API_MODE_ALT1, \
              .pull=GPIO__PULL_UP, \
              .logic_level=GPIO_LVL_HI,  \
             },     \
    .GpioSdOut={.pad = {.port=PORT_C, .pin=3}, \
               .connector2="J3.35",   \
               .mux = 5, \
               .dir=GPIO_DIR_OUT, \
               .name="I2S2_SD",    \
               .mode = GPIO_API_MODE_ALT1, \
               .pull=GPIO__PULL_UP, \
               .logic_level=GPIO_LVL_HI, },



#else
#define I2S2_COMMON_GPIO_VARIABLES
#endif



#ifdef HAS_I2S2

bool I2s2CallBackTxHalf(void){
    bool res = false ;
    res = I2sDmaCallBackTxHalf(2);
    return res;
};

bool I2s2CallBackTxDone(void){
    bool res = false ;
    res = I2sDmaCallBackTxDone(2);
    return res;
};


bool I2s2CallBackRxHalf(void){
    bool res = false;
    res= I2sDmaCallBackRxHalf(2);
    return res;
};

bool I2s2CallBackRxDone(void){
    bool res = false;
    res = I2sDmaCallBackRxDone(2);
    return res;
};

static uint16_t I2s2TxSampleArray[I2S_MEM_SIZE]={0};
static uint16_t I2s2RxSampleArray[I2S_MEM_SIZE]={0};

#define I2S_CONFIG_I2S2                                               \
    {                                                                 \
         I2S2_COMMON_GPIO_VARIABLES                                   \
        .CallBackTxHalf = I2s2CallBackTxHalf ,                        \
        .CallBackTxDone = I2s2CallBackTxDone,                         \
        .CallBackRxHalf = I2s2CallBackRxHalf,                         \
        .CallBackRxDone = I2s2CallBackRxDone,                         \
        .dma_channel_tx_num=DMA_CHANNEL_NUM_I2S2_TX,                  \
        .dma_channel_rx_num=DMA_CHANNEL_NUM_I2S2_RX,                  \
        .num = 2,                                                     \
        .led_tx_num = 1,                                              \
        .led_rx_num = 1,                                              \
        .dir_role = I2S_DIR_BUS_MODE_MASTER_TX,                       \
        .sample_mode = SAMPLE_MODE_STEREO,                            \
        .direction = CONNECT_DIR_TRANSMIT,                            \
        .audio_frequency_hz = AUDIO_FREQ_96K,                         \
        .bus_role = IF_BUS_ROLE_MASTER ,                              \
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
        .name = "WavPlayer",                                          \
        .valid=true,                                                  \
    },
#else
#define I2S_CONFIG_I2S2
#endif

/*constant compile-time known settings*/
const I2sConfig_t I2sConfig[] = {
        I2S_CONFIG_I2S2
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
    {        .num = 1, 		.valid=true,    },
#endif

#ifdef HAS_I2S2
    {        .num = 2,		.valid=true,    },
#endif

#ifdef HAS_I2S3
    {        .num = 3,		.valid=true,    },
#endif
};

COMPONENT_GET_CNT(I2s, i2s)

