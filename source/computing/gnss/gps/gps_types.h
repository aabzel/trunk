#ifndef GPS_TYPES_H
#define GPS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "gps_const.h"
#include "data_types.h"
#if 0
//error bit field

typedef union {
    uint8_t byte;
    struct {
        uint8_t sig0 : 1;/*bit 7: sample3 SIGN old*/
        uint8_t sig1 : 1;/*bit 6: sample2 SIGN*/
        uint8_t sig2 : 1;/*bit 5: sample1 SIGN*/
        uint8_t sig3 : 1;/*bit 4: sample0 SIGN new*/

        uint8_t mag0 : 1;/*bit 3: sample3 MAG old*/
        uint8_t mag1 : 1;/*bit 2: sample2 MAG*/
        uint8_t mag2 : 1;/*bit 1: sample1 MAG*/
        uint8_t mag3 : 1;/*bit 0: sample0 MAG new*/
    };
} GnssFpgaPackByte_t;

typedef union {
    uint8_t byte;
    struct {
        uint8_t mag3 : 1;/*bit 0: sample0 MAG new*/
        uint8_t mag2 : 1;/*bit 1: sample1 MAG*/
        uint8_t mag1 : 1;/*bit 2: sample2 MAG*/
        uint8_t mag0 : 1;/*bit 3: sample3 MAG old*/

        uint8_t sig3 : 1;/*bit 4: sample0 SIGN new*/
        uint8_t sig2 : 1;/*bit 5: sample1 SIGN*/
        uint8_t sig1 : 1;/*bit 6: sample2 SIGN*/
        uint8_t sig0 : 1;/*bit 7: sample3 SIGN old*/
    };
} GnssFpgaPackByte_t;
#endif

typedef union {
    uint8_t byte;
    struct {
        uint8_t mag0 : 1;/*bit 0: sample3 MAG old*/
        uint8_t mag1 : 1;/*bit 1: sample2 MAG*/
        uint8_t mag2 : 1;/*bit 2: sample1 MAG*/
        uint8_t mag3 : 1;/*bit 3: sample0 MAG new*/

        uint8_t sig0 : 1;/*bit 4: sample3 SIGN old*/
        uint8_t sig1 : 1;/*bit 5: sample2 SIGN*/
        uint8_t sig2 : 1;/*bit 6: sample1 SIGN*/
        uint8_t sig3 : 1;/*bit 7: sample0 SIGN new*/
    };
} GnssFpgaPackByte_t;

typedef struct {
    size_t offset_samples ; /*sample offset on min correlation I*/
    int32_t mult_summ;  /*max correlation value I*/
    double if_corr_hz; /*doppler*/
}CorrelationResult_t;

typedef struct {
    int32_t mult_summ;  /*max abs correlation value I*/
    size_t offset_samples; /*max abs correlation value*/
}PrnCorrelationResult_t;

typedef struct {
    int prn;
    int32_t if_corr_hz; /*doppler*/
    PrnCorrelationResult_t Max; /*sqrt(I + Q)*/
}PrnInfo_t;


typedef struct {
    int prn;
    uint32_t init_prn_phase_sample;
    double doppler_offset_hz;
    bool valid;
   	//int32_t mult_summ_max;  /*max correlation value I*/
   	//int32_t mult_summ_min;  /*max correlation value I*/
    //size_t s_max ; /*sample offset on max correlation I*/
    //size_t s_min ; /*sample offset on min correlation I*/
    //size_t prn_offset_samples;

   // uint32_t if_seek_start_hz; /*offset*/
   // uint32_t if_seek_end_hz;/*offset*/
    uint32_t if_seek_step_hz;
    uint32_t doppler_range_hz;

   // uint32_t if_hz; /* set intermediate freq*/

    //int32_t if_min_corr_hz; /*doppler*/
    //int32_t if_max_corr_hz; /*doppler*/

    CorrelationResult_t CorrelationMax; // sqrt corr
    //CorrelationResult_t CorrelationMin;
    //CorrelationResult_t CorrelationMax;
}GpsSat_t;

typedef struct {
    bool valid;
    int prn;
}GpsSatHandle_t;


#define GPS_COMMON_VARIABLES                 \
    uint8_t num;                             \
    bool valid;                              \
    uint32_t step_samples;                   \
    uint8_t histogram_num ;                  \
    double gnss_front_end_lo_freq_hz;        \
    double adc_sample_rate_hz; \
    GpsSat_t* SatS; \
    uint8_t sat_cnt; \
    size_t seek_start_sample; /*start prn offset */     \
    char* file_name;

typedef struct {
    GPS_COMMON_VARIABLES
}GpsConfig_t;

#define PACKED_BUF_SIZE        4096
typedef struct {
    GPS_COMMON_VARIABLES
    FILE *FilePtr;
    int32_t size_bytes;
    uint32_t sample_cnt;
    uint32_t one_prn_sample_cnt;
    double intermediate_freq_hz;
    double sample_per_chip;
    double duration_s;
    double adc_sample_time_s;
    double adc_sample_len_m;

    uint32_t prn_phase_seek_start_sample;
    uint32_t prn_phase_seek_end_sample;

    uint64_t bytes_read ;

    int8_t SignalI[TWO_PRN_SAMPLE_CNT];
    int8_t SignalQ[TWO_PRN_SAMPLE_CNT];
   // int8_t SignalIQmix[TWO_PRN_SAMPLE_CNT];

    uint8_t packed_data_buf[PACKED_BUF_SIZE];
}GpsHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* GPS_TYPES_H  */
