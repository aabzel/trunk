#ifndef I2S_MCAL_TYPES_H
#define I2S_MCAL_TYPES_H

#ifdef HAS_COMPLEX
#include <complex.h>
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "i2s_const.h"
#include "audio_types.h"
#include "data_types.h"
#include "interfaces_const.h"
#include "connectivity_const.h"

#ifdef HAS_DFT
#include "dft_types.h"
#endif

#ifdef HAS_I2S_DMA
#include "dma_types.h"
#endif
#include "i2s_const.h"
#include "i2s_custom_types.h"
#include "interfaces_types.h"

#ifndef I2S_CUSTOM_VARIABLES
#define I2S_CUSTOM_VARIABLES
#endif

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef struct {
    SampleType_t left;
    SampleType_t right;
}I2sSampleType_t;


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
#define I2S_DMA_COMMON_VARIABLES                \
    DmaPad_t Dma;                               \
    DmaIsrHandler_t CallBackTxHalf;             \
    DmaIsrHandler_t CallBackTxDone;             \
    DmaIsrHandler_t CallBackRxHalf;             \
    DmaIsrHandler_t CallBackRxDone;
#else
#define I2S_DMA_COMMON_VARIABLES
#endif

#define I2S_COMMON_VARIABLES     \
    I2S_DMA_COMMON_VARIABLES     \
    uint32_t audio_freq_hz;      \
    ConnectivitDir_t direction;  \
    IfBusRole_t bus_role;        \
    uint8_t debug_led1_num;      \
    uint8_t debug_led2_num;      \
    uint8_t irq_priority;        \
    I2sMode_t mode;              \
    uint8_t num;                 \
    Pad_t PadDebug1;             \
    Pad_t PadDebug2;             \
    SampleMode_t sample_mode;    \
    uint32_t samples_cnt;        \
    I2sDataFormat_t data_format; \
    bool valid;

typedef struct {
    I2S_COMMON_VARIABLES
    uint32_t base;
    uint32_t sck_freq_hz;
    uint8_t int_num;
    char *name;
    FullDuplex_t full_duplex;
    Cpol_t  cpol;
    MclkOut_t mclk_out;
    Standard_t standard;
    I2sClockSource_t clock_source;
    I2sFlashFsParamsId_t ParamId;
#ifdef HAS_GPIO
    GpioConfig_t GpioSck;
    GpioConfig_t GpioLrCk;
    GpioConfig_t GpioSdOut;
    GpioConfig_t GpioSdIn;
    GpioConfig_t GpioMClk;
#endif /**/

#ifdef HAS_COMPLEX
    const double complex* const dft_mem;
#endif
}I2sConfig_t;

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


#define I2S_DMA_ISR_VARIABLES                               \
    volatile bool rx_half;                  \
    volatile bool rx_done;                  \
    volatile bool tx_half;                  \
    volatile bool tx_done;                  \
    volatile uint32_t dma_move_cnt;             \
    volatile uint32_t tx_half_cnt;             \
    volatile uint32_t tx_done_cnt;                  \
    volatile uint32_t rx_half_cnt;             \
    volatile uint32_t rx_done_cnt;


#define I2S_ISR_TX_VARIABLES                               \
    volatile Type64Union_t tx_sample_fixed;             \
    volatile Type64Union_t tx_sample;             \
    volatile uint32_t tx_sample_cnt;           \
    volatile uint8_t cur_tx_track;             \
    volatile SampleType_t TxBuffer[I2S_BUFFER_SIZE];   \
    volatile uint8_t tx_buff_empty_cnt;        \
    volatile uint8_t prev_tx_track;            \
    volatile bool tx_buff_empty;     \
    volatile bool play;

#define  I2S_ISR_RX_VARIABLES \
    volatile Type64Union_t rx_sample_fixed;       \
    volatile Type64Union_t rx_sample;             \
    volatile uint32_t rx_toggle_cnt;              \
    volatile bool rx_buff_full;                   \
    volatile bool rec;                            \
    volatile bool rx_int;                         \
    volatile uint32_t rx_buff_full_cnt;           \
    volatile uint8_t cur_rx_track;                \
    volatile SampleType_t RxBuffer[I2S_BUFFER_SIZE];   \
    volatile uint8_t rx_byte;

#define  I2S_ISR_TX_RX_VARIABLES   \
    volatile bool rx_tx_done;                  \
    volatile uint32_t rx_tx_done_cnt;

#define I2S_ISR_VARIABLES                               \
    I2S_ISR_TX_RX_VARIABLES    \
    I2S_ISR_TX_VARIABLES    \
    I2S_ISR_RX_VARIABLES    \
    I2S_DMA_ISR_VARIABLES    \
    volatile Type64Union_t calc_sample_fixed;             \
    volatile uint32_t it_cnt;                  \
    volatile FlowCnt_t cnt;                    \
    volatile bool stop_needed;                 \
    volatile bool it_done;                     \
    volatile bool next;             \
    volatile bool busy;             \
    volatile bool need_new_data;             \
    volatile bool switch_needed;             \
    volatile I2sState_t state; \
    volatile bool in_progress;     \
    volatile uint32_t status_stop_cnt;     \
    volatile int32_t frames;                             \
    volatile uint32_t total_stop_cnt;                  \
    volatile uint32_t toggle_cnt;

    //volatile SampleType_t RxBuffer[2][I2S_BUFFER_SIZE];

typedef struct {
    size_t cnt; /*ISR cnt*/
    size_t index ;
    size_t overflow ;
    size_t size ; /*samples (1 sample = 8 , 16 or 32 bit)*/
    SampleType_t* array ;
}SampleStream_t;

typedef struct {
    I2S_COMMON_VARIABLES

    I2S_CUSTOM_VARIABLES

    I2S_ISR_VARIABLES

#ifdef HAS_DDS
    uint8_t dac_num; /*associated with i2s dac*/
#endif /*HAS_DDS*/

    bool echo;
    bool loopback;
    bool iir;
    bool dac;
    double max_diration_s;
    bool rx_it_proc_done;
    uint8_t rx_byte_it;
    uint32_t tx_time_out;
    U32Value_t tx_rate;
    U32Value_t rx_rate;
    I2sErr_t Err;
    FlowCnt_t cnt_prev;
    uint32_t error_cnt_prev;
    uint32_t error_cnt;
    uint32_t play_off_time_stamp_ms;
    uint32_t rec_off_time_stamp_ms;

    SampleStream_t Rx;
    SampleStream_t Tx;

    size_t frames_to_send;

#ifdef HAS_DFT
    double complex* dft_mem;
    //double max_freq_hz;
    double exp_freq_hz;
    Spectr_t maxFreq;
#endif /**/

    bool init_done;
    bool proc_on; /*Proc in super loop*/
#ifdef HAS_I2S_VOLUME
    I2sState_t state;
    SampleType_t pcm_max_set;
    SampleType_t pcm_max_get;
    SampleType_t dec_numerator;
    SampleType_t denominator;
    SampleType_t inc_numerator;
#endif
} I2sHandle_t;

typedef struct {
    bool num;
    I2sDirRole_t i2s_bus_dir;
    IfBusRole_t bus_role;
    ConnectivitDir_t direction;
    bool valid;
} I2sBusDirInfo_t;

#endif /* I2S_MCAL_TYPES_H */
