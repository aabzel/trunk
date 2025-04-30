#ifndef BPSK_TYPES_H
#define BPSK_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bpsk_const.h"
#include "interfaces_const.h"
#include "audio_types.h"
#include "dsp_types.h"

typedef int16_t BpskSample_t;

#define BPSK_DECODER_COMMON_VALIABLE       \
    DspFilterType_t filter_loop_type;      \
    uint32_t filter_order;                 \
    uint32_t filter_loop_cuf_off_freq_hz;  \
    uint8_t filter_loop_num;
    //uint8_t filter_i_num;
    //uint8_t filter_q_num;

#define BPSK_SDR_COMMON_VALIABLE        \
    uint32_t sampling_frequency_hz;     \
    uint8_t sample_size_bit;            \
    uint8_t dds_num;

#define BPSK_COMMON_VALIABLE            \
    BPSK_DECODER_COMMON_VALIABLE        \
    BPSK_SDR_COMMON_VALIABLE            \
    IfBitOrder_t bit_order;             \
    uint8_t pid_phase_err_num;          \
    uint8_t quadrature_mixer_num;       \
    uint32_t bit_rate;                  \
    uint32_t amplitude;                 \
    uint32_t carrier_frequency_hz;      \
    uint8_t num;                        \
    uint8_t decimator_num;              \
    bool valid;                         \
    char* LogFileName;                  \
    char* name;

typedef struct {
    BPSK_COMMON_VALIABLE
} BpskConfig_t;

#if 0
typedef struct {
    double  LocalOcs;
    double  AfterMux;
    FirSample_t  AfterFilt;
}SdrData_t;
#endif

#define BPSK_DECODER_VARIABLE     \
    uint32_t decoded_byte_cnt; /* number of bytes demodulated*/   \
    uint32_t bit_rx_cnt;   \
    uint32_t data_size_bytes; /* number of bytes in sample array*/ \
    double time_s;   \
    uint8_t* BinDataArray; \
    double real_sample;   \
    double s_feed_back;   \
    double s_feed_back_sin;   \
    double s_feed_back_sin_arg;   \
    double lo_phase_rad;          \
    double lo_phase_err_rad;   \
    int8_t data;

#if 0
    SdrData_t SdrQ;
    SdrData_t SdrI;
#endif

#define BPSK_ENCODER_VARIABLE     \
    double sample_time_s;         \
    double carrier_period_s;      \
    double chip_dutation_s;       \
    uint32_t sample_per_chip;     \
    uint32_t carrier_periods_per_chip;

typedef struct {
    BPSK_COMMON_VALIABLE
    BPSK_ENCODER_VARIABLE
    BPSK_DECODER_VARIABLE
    bool init;
    SampleType_t sample;
    uint32_t sample_cnt; // number of samples in sample array
    SampleType_t* samples;// sample array pointer
} BpskHandle_t;

#ifdef __cplusplus
}
#endif

#endif /*BPSK_TYPES_H*/
