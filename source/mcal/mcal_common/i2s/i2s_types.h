#ifndef I2S_MCAL_TYPES_H
#define I2S_MCAL_TYPES_H

#ifdef HAS_COMPLEX
#include <complex.h>
#endif

#include <stddef.h>

#include "std_includes.h"
#include "i2s_const.h"
#include "audio_types.h"
#include "data_types.h"
#include "interfaces_const.h"
#include "connectivity_const.h"
#include "i2s_const.h"
#include "interfaces_types.h"
#include "mcal_const.h"

#ifdef HAS_I2S_DMA
#include "dma_types.h"
#include "dma_channel_types.h"
#endif

#ifdef HAS_I2S_CUSTOM
#include "i2s_custom_types.h"
#else
#define I2S_CUSTOM_VARIABLES
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef struct {
    uint32_t cnt; /*ISR cnt*/
    uint32_t index ;
    uint32_t overflow ;
    uint32_t size ; /*samples (1 sample = 8 , 16 or 32 bit)*/
    SampleType_t* array ;
}SampleStream_t;

typedef struct  {
    uint32_t cnt;
    uint32_t busy;
    uint32_t write;
    uint32_t read;
    uint32_t next;
    uint32_t rx_next;
    uint32_t tx_next;
    uint32_t start;
}I2sErr_t;

typedef struct {
    SampleType_t left;
    SampleType_t right;
}I2sSampleType_t;

typedef struct {
    bool num;
    IfBusRole_t bus_role;
    ConnectivitDir_t direction;
#if 0
#endif
    bool valid;
} I2sBusDirInfo_t;


typedef struct {
    uint16_t bus_role;
}I2sFlashFsParamsId_t;

typedef union {
    uint8_t buff[4];
    uint8_t sample8[4];
    uint16_t sample16[2];
    uint32_t sample24;
    uint32_t sample32;
}I2sSample_t;

typedef union {
    uint8_t data[2];
    struct{
        int8_t right;
        int8_t left;
    };
}I2s8BitSample_t;

typedef union {
    uint8_t data[4];
    struct{
        int16_t right;
        int16_t left;
    };
    struct{
        uint16_t u_right;
        uint16_t u_left;
    };
}I2s16BitSample_t;

typedef union {
    uint8_t data[8];
    struct{
        int32_t right;
        int32_t left;
    };
    struct{
        uint32_t u_right;
        uint32_t u_left;
    };
}I2s32BitSample_t;

typedef union {
    uint8_t buff[8];
    I2sSample_t sample[2];
}I2sRlSample_t;

#ifdef HAS_I2S_DMA
#define I2S_DMA_COMMON_VARIABLES       \
    uint8_t dma_channel_tx_num;        \
    uint8_t dma_channel_rx_num;        \
    DmaIsrHandler_t CallBackTxHalf;    \
    DmaIsrHandler_t CallBackTxDone;    \
    DmaIsrHandler_t CallBackRxHalf;    \
    DmaIsrHandler_t CallBackRxDone;
#else
#define I2S_DMA_COMMON_VARIABLES
#endif

#ifdef HAS_GPIO
#define I2S_COMMON_GPIO_VARIABLES     \
    GpioConfig_t GpioSck;             \
    GpioConfig_t GpioLrCk;            \
    GpioConfig_t GpioSdOut;           \
    GpioConfig_t GpioSdIn;            \
    GpioConfig_t GpioMClk;

#else
#define I2S_COMMON_GPIO_VARIABLES
#endif

#define I2S_DEBUG_GPIO_VARIABLES           \
    Pad_t PadDmaRx;                        \
    Pad_t PadDmaTx;

#define I2S_DEBUG_VARIABLES           \
    uint8_t led_tx_num;               \
    uint8_t led_rx_num;               \

#define I2S_BASE_VARIABLES            \
    I2sMclkOut_t mclk_out;            \
    I2sStandard_t standard;           \
    I2sClockSource_t clock_source;    \
    DspSampleMode_t sample_mode;      \
    I2sFullDuplex_t full_duplex;      \
    ConnectivitDir_t direction;       \
    IfBusRole_t bus_role;             \
    I2sDataFormat_t data_format;      \
    uint32_t audio_frequency_hz;

#define I2S_BUFFER_VARIABLES          \
    uint16_t* TxArray;                \
    uint16_t* RxArray;                \
    uint32_t samples_cnt;

#define I2S_COMMON_VARIABLES          \
    I2S_BASE_VARIABLES                \
    I2S_DEBUG_GPIO_VARIABLES          \
    I2S_DEBUG_VARIABLES               \
    I2S_DMA_COMMON_VARIABLES          \
    I2S_COMMON_GPIO_VARIABLES         \
    I2S_BUFFER_VARIABLES              \
    I2sCpol_t  cpol;                  \
    uint8_t irq_priority;             \
    MoveMode_t move_mode;             \
    uint8_t num;                      \
    char *name;                       \
    bool valid;

typedef struct {
    I2S_COMMON_VARIABLES
    uint32_t sck_freq_hz;
    uint8_t int_num;
    I2sFlashFsParamsId_t ParamId;

#ifdef HAS_COMPLEX
    const float complex* const dft_mem;
#endif
}I2sConfig_t;


#define I2S_DMA_TX_ISR_VARIABLES            \
    volatile bool tx_half;                  \
    volatile bool tx_done;                  \
    volatile uint32_t tx_half_cnt;          \
    volatile uint32_t tx_done_cnt;

#define I2S_DMA_RX_ISR_VARIABLES            \
    volatile bool rx_half;                  \
    volatile bool rx_done;                  \
    volatile uint32_t rx_half_cnt;          \
    volatile uint32_t rx_done_cnt;

#define I2S_DMA_ISR_VARIABLES             \
        I2S_DMA_TX_ISR_VARIABLES          \
        I2S_DMA_RX_ISR_VARIABLES          \
        volatile uint32_t dma_move_cnt;


#define I2S_ISR_TX_VARIABLES                                        \
    volatile uint32_t play_off_time_stamp_ms;                       \
    volatile bool tx_int;                                           \
    volatile uint32_t tx_cnt;                                       \
    volatile uint32_t tx_time_out;                                  \
    volatile U32Value_t tx_rate;                                    \
    volatile uint32_t tx_half_int;                                  \
    volatile SampleStream_t Tx;                                     \
    volatile Type64Union_t tx_sample_fixed;                \
    volatile Type64Union_t tx_sample;                      \
    volatile uint32_t tx_sample_cnt;                       \
    volatile uint8_t cur_tx_track;                         \
    volatile uint8_t tx_buff_empty_cnt;                    \
    volatile uint8_t prev_tx_track;                        \
    volatile bool tx_buff_empty;                           \
    volatile bool play;

#define  I2S_ISR_RX_VARIABLES                          \
    SampleStream_t Rx;                                 \
    bool rx_it_proc_done;                              \
    uint32_t rec_off_time_stamp_ms;                    \
    uint8_t rx_byte_it;                                \
    uint32_t rx_cnt;                                   \
    uint32_t rx_buff_size;                             \
    U32Value_t rx_rate;                                \
    volatile Type64Union_t rx_sample_fixed;            \
    volatile Type64Union_t rx_sample;                  \
    volatile uint32_t rx_toggle_cnt;                   \
    volatile bool rx_buff_full;                        \
    volatile bool rec;                                 \
    volatile bool rx_int;                              \
    volatile uint32_t rx_buff_full_cnt;                \
    volatile uint8_t cur_rx_track;                     \
    volatile uint8_t rx_byte;

#define  I2S_ISR_TX_RX_VARIABLES               \
    volatile bool rx_tx_done;                  \
    volatile uint32_t rx_tx_done_cnt;

#define I2S_ISR_VARIABLES                               \
    I2S_ISR_TX_RX_VARIABLES                             \
    I2S_ISR_TX_VARIABLES                                \
    I2S_ISR_RX_VARIABLES                                \
    I2S_DMA_ISR_VARIABLES                               \
    volatile Type64Union_t calc_sample_fixed;           \
    volatile uint32_t it_cnt;                           \
    volatile FlowCnt_t cnt;                             \
    volatile bool stop_needed;                          \
    volatile bool it_done;                              \
    volatile bool next;                                 \
    volatile bool busy;                                 \
    volatile bool need_new_data;                        \
    volatile bool switch_needed;                        \
    volatile I2sState_t state;                          \
    volatile bool in_progress;                          \
    volatile uint32_t status_stop_cnt;                  \
    volatile int32_t frames;                            \
    volatile uint32_t total_stop_cnt;                   \
    volatile uint32_t toggle_cnt;

    //volatile SampleType_t RxBuffer[2][I2S_BUFFER_SIZE];


#ifdef HAS_I2S_VOLUME
#define I2S_VARIABLE_VOLUME                   \
    I2sState_t state;                         \
    SampleType_t pcm_max_set;                 \
    SampleType_t pcm_max_get;                 \
    SampleType_t dec_numerator;               \
    SampleType_t denominator;                 \
    SampleType_t inc_numerator;

#else
#define I2S_VARIABLE_VOLUME
#endif

#define I2S_ERROR_VARIABLES               \
    I2sErr_t Err;                         \
    bool error;                           \
    uint32_t error_cnt_prev;              \
    uint32_t error_cnt;

typedef struct {
    I2S_COMMON_VARIABLES
    I2S_CUSTOM_VARIABLES
    I2S_ISR_VARIABLES
    I2S_VARIABLE_VOLUME
    I2S_ERROR_VARIABLES
    bool echo;
    bool loopback;
    bool iir;
    bool dac;
    bool init_done;
    bool proc_on;
    float max_diration_s;
    FlowCnt_t cnt_prev;
    uint32_t frames_to_send;
    /*Proc in super loop*/
} I2sHandle_t;

#endif /* I2S_MCAL_TYPES_H */
