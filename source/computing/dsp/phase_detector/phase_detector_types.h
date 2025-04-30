#ifndef PHASE_DETECTOR_TYPES_H
#define PHASE_DETECTOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "phase_detector_const.h"
#include "circular_buffer_types.h"

typedef int16_t PhaseDetectorSample_t;

#define PHASE_DETECTOR_COMMON_VARIABLE     \
    uint32_t num;                          \
    uint32_t filter_order;                 \
    uint16_t channel_cnt;                  \
    uint16_t bitsPerSample;/**/            \
    uint32_t sample_freq_hz;               \
    double cut_off_frequency_hz;           \
    double signal_frequency_hz;            \
    double speed_of_sound_m_per_s;         \
    uint8_t quadrature_mixer_num;          \
    char* name;                            \
    bool valid;                            \

typedef struct {
    PHASE_DETECTOR_COMMON_VARIABLE
    /*Array of coefficients*/
} PhaseDetectorConfig_t;

typedef struct {
    PHASE_DETECTOR_COMMON_VARIABLE
    bool init;
    double wavelength_m;                   \
    double duration_s;
    double sample_time_s;
    uint32_t sample_cnt;
    uint32_t proc_cnt;
    /*Array of values*/
} PhaseDetectorHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* PHASE_DETECTOR_TYPES_H */
