#ifndef I2S_GENERAL_TYPES_H
#define I2S_GENERAL_TYPES_H

#ifdef HAS_COMPLEX
#include <complex.h>
#endif
#include <stdbool.h>
#include <stdint.h>

#include "i2s_const.h"
#include "audio_types.h"
#include "data_types.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif


#ifdef HAS_NRFX_I2S
#include "i2s_nrf_types.h"
#include "nrfx_i2s.h"
#endif /*HAS_NRFX_I2S*/

#ifdef HAS_NRFX_GPIO
#include "gpio_custom_types.h"
#endif

#ifdef HAS_ZEPHYR_I2S
#include "i2s_zephyr_types.h"
#endif /*HAS_ZEPHYR_I2S*/

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2s.h"
#endif /*USE_HAL_DRIVER*/

#include "i2s_const.h"

typedef struct {
    uint16_t bus_role;
}FlashFsParamsId_t;

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

#define I2S_COMMON_VARIABLES     \
    uint8_t num;                 \
    uint8_t debug_led1_num;      \
    uint8_t debug_led2_num;      \
    bool valid;                  \
    SampleMode_t sample_mode;    \
    uint32_t samples_cnt;        \
    I2sDataFormat_t data_format; \
    AudioFreq_t audio_freq;


typedef struct {
	I2S_COMMON_VARIABLES
    uint32_t base;
    uint32_t sck_freq_hz;
    uint8_t int_num;
    char *name;
    FullDuplex_t full_duplex;
    Cpol_t  cpol;
    I2sRole_t mode;
    MclkOut_t mclk_out;
    Standard_t standard;
    I2sClockSource_t clock_source;
    FlashFsParamsId_t ParamId;
#ifdef HAS_GPIO
    Pad_t PadSck;
    Pad_t PadLrCk;
    Pad_t PadSdOut;
    Pad_t PadSdIn;
    Pad_t PadMClk;
#endif /**/

#ifdef HAS_I2S_NRFX
    nrfx_i2s_data_handler_t I2sIsrHandler;
#endif /*HAS_I2S_NRFX*/

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

typedef struct {
    I2S_COMMON_VARIABLES

    I2S_CUSTOM_VARIABLES

#ifdef HAS_SW_DAC
    uint8_t dac_num; /*associated with i2s dac*/
#endif /*HAS_SW_DAC*/

    bool echo;
    bool loopback;
    bool iir;
    bool dac;
    bool play;
    bool rx_it_proc_done;
    volatile bool tx_int;
    volatile bool tx_half_int;
    volatile bool in_progress;
    volatile bool rx_int;
    volatile bool rx_half_int;
    volatile uint8_t rx_byte;
    uint8_t rx_byte_it;
    uint32_t tx_time_out;
    volatile uint32_t status_stop_cnt;
    volatile int32_t frames;
    volatile uint32_t total_stop_cnt;
    volatile uint32_t toggle_cnt;
    U32Value_t tx_rate;
    U32Value_t rx_rate;
    volatile flowCnt_t cnt;
    volatile bool stop_needed;
    volatile bool next;
    volatile bool need_new_data;
    volatile bool switch_needed;
    I2sErr_t Err;
    flowCnt_t cnt_prev;
    volatile Type64Union_t rx_sample_fixed;
    volatile Type64Union_t calc_sample_fixed;
    volatile Type64Union_t tx_sample_fixed;
    volatile Type64Union_t rx_sample;
    volatile Type64Union_t tx_sample;
    uint32_t error_cnt_prev;
    uint32_t error_cnt;
    volatile uint32_t rx_half_cnt;
    volatile uint32_t tx_half_cnt;
    volatile uint32_t rx_cnt;
    volatile uint32_t rx_toggle_cnt;
    volatile uint32_t tx_cnt;
    volatile uint32_t it_cnt;
    volatile uint32_t tx_sample_cnt;
#ifdef USE_HAL_DRIVER
    I2S_HandleTypeDef i2s_h;
#endif /*USE_HAL_DRIVER*/
    size_t frames_to_send;

    volatile uint8_t cur_tx_track;
    volatile bool rx_tx_done;
    volatile uint8_t prev_tx_track;
    volatile uint8_t cur_rx_track;
#ifdef HAS_DFT
    double complex* dft_mem;
#endif
    volatile SampleType_t TxBuffer[2][I2S_BUFFER_SIZE];
    volatile SampleType_t RxBuffer[2][I2S_BUFFER_SIZE];

    bool init_done;
#ifdef HAS_I2S_VOLUME
    I2sState_t state;
    SampleType_t pcm_max_set;
    SampleType_t pcm_max_get;
    SampleType_t dec_numerator;
    SampleType_t denominator;
    SampleType_t inc_numerator;
#endif
} I2sHandle_t;

#endif /* I2S_GENERAL_TYPES_H */
