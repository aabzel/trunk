#ifndef BPSK_4FS_TYPES_H
#define BPSK_4FS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bpsk_4fs_const.h"
#include "interfaces_const.h"
#include "dsp_types.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

typedef int16_t Bpsk4fsSample_t;

#define BPSK_4FS_DECODER_COMMON_VALIABLE       \
    DspFilterType_t filter_loop_type;          \
    uint8_t* BinDataArray;                                         \
    uint32_t data_size_bytes; /* number of bytes in sample array*/ \
    int32_t bit_rx_phase;                      \
    uint8_t quad_mix_4fs_num;                  \
    uint32_t filter_order;                     \
    uint8_t decimator_num;                     \
    uint8_t pid_num;                           \
    uint8_t adc_num;                           \
    uint32_t filter_loop_cuf_off_freq_hz;      \
    uint8_t filter_loop_num;
    //uint8_t filter_i_num;
    //uint8_t filter_q_num;

#define BPSK_4FS_SDR_COMMON_VALIABLE        \
    uint32_t sampling_frequency_hz;     \
    uint8_t sample_size_bit;            \
    uint8_t dds_num;


#ifdef HAS_GPIO
#define BPSK_4FS_COMMON_GPIO_VALIABLE      \
        Pad_t PadData;                     \
        Pad_t PadClk;

#else
#define BPSK_4FS_COMMON_GPIO_VALIABLE
#endif

#define BPSK_4FS_COMMON_VALIABLE            \
    BPSK_4FS_DECODER_COMMON_VALIABLE        \
    BPSK_4FS_SDR_COMMON_VALIABLE            \
    BPSK_4FS_COMMON_GPIO_VALIABLE           \
    IfBitOrder_t bit_order;                 \
    uint8_t dc_cut_filter_num;              \
    uint8_t pid_phase_err_num;              \
    uint32_t amplitude;                 \
    uint32_t bit_rate;                  \
    uint32_t carrier_frequency_hz;      \
    uint8_t num;                        \
    bool valid;                         \
    char* LogFileName;                  \
    char* name;

typedef struct {
    BPSK_4FS_COMMON_VALIABLE
} Bpsk4fsConfig_t;

#if 0
typedef struct {
    float  LocalOcs;
    float  AfterMux;
    FirSample_t  AfterFilt;
}SdrData_t;
#endif

#define BPSK_4FS_DECODER_VARIABLE                                  \
    uint32_t decoded_byte_cnt; /* number of bytes demodulated*/    \
    uint32_t bit_rx_cnt;                                           \
    uint8_t rx_byte;                                               \
    float time_s;                                                  \
    float s_feed_back;                                             \
    float s_feed_back_sin;                                         \
    float s_feed_back_sin_arg;                                     \
    int8_t data;


#define BPSK_4FS_ARRAY_VARIABLE                                        \
    uint32_t sample_cnt;    /* number of samples in sample array */    \
    int32_t* samples;       /* sample array pointer    */

#define BPSK_4FS_ENCODER_VARIABLE       \
    float sample_time_s;                \
    float carrier_period_s;             \
    float chip_dutation_s;              \
    uint32_t sample_per_chip;           \
    uint32_t carrier_periods_per_chip;

typedef struct {
    BPSK_4FS_COMMON_VALIABLE
    BPSK_4FS_ENCODER_VARIABLE
    BPSK_4FS_DECODER_VARIABLE
    BPSK_4FS_ARRAY_VARIABLE
    bool init;
    int32_t sample;
    uint32_t sam_n; // up time in sample number units
    uint32_t half_cplt_done_cnt_prev;
    uint32_t chan_conv_end_cnt_prev;
    uint32_t error_cnt;
    uint32_t lost_block;
    uint32_t spin;
} Bpsk4fsHandle_t;

#ifdef __cplusplus
}
#endif

#endif /*BPSK_4FS_TYPES_H*/
