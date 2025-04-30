#ifndef QUADRATURE_MIXER_TYPES_H
#define QUADRATURE_MIXER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "quadrature_mixer_const.h"
#include "dsp_types.h"

typedef struct {
    double LocalOcs;
    double AfterMux;
    FilterSample_t AfterFilt;
}SdrData_t;

typedef double QuadratureMixerSample_t;

#define QUADRATURE_MIXER_COMMON_VARIABLE        \
    uint8_t filter_num[2];                      \
    DspFilterType_t filter_type;                \
    uint32_t sample_rate_hz;                    \
    uint32_t cut_off_freq_hz;                   \
    uint32_t filter_order;                      \
    uint32_t num;                               \
    char* name;                                 \
    bool valid;

typedef struct {
    QUADRATURE_MIXER_COMMON_VARIABLE
} QuadratureMixerConfig_t;

typedef struct {
    QUADRATURE_MIXER_COMMON_VARIABLE
    double time_s; // in
    double sample; // in
    double lo_phase_rad; // in
    double lo_frequency_hz; // in
    double phase_error_rad; // out
    bool init;
    uint32_t proc_cnt;
    SdrData_t SdrI; //out
    SdrData_t SdrQ; //out
} QuadratureMixerHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* QUADRATURE_MIXER_TYPES_H */
