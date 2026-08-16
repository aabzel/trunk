#ifndef DSP_MCAL_TYPES_H
#define DSP_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "dsp_const.h"
#include "bit_types.h"

typedef struct {
    uint32_t sample ;
    int64_t correlation;
    int64_t abs_correlation;
    float correlation_log;
} CorrelationInfo_t;

typedef struct {
    double frequency_hz;
    double amplitude;
    uint32_t i;
}Spectr_t;

typedef union {
    uint8_t u8[3];
    int8_t s8[3];
    BitField24_t bits24;
} Sample24bit_t;

typedef int8_t Gain_t;


#ifdef HAS_PCM_DOUBLE
typedef double SampleType_t;
#endif

#ifdef HAS_PCM_FLOAT
typedef float SampleType_t;
#endif

#ifdef HAS_PCM_U16
typedef uint16_t SampleType_t;
#endif

#ifdef HAS_PCM_S16
//typedef int32_t FilterSample_t;
typedef int16_t SampleType_t;
#endif

#ifdef HAS_PCM_S32
typedef int32_t SampleType_t;
#endif

typedef float FilterSample_t;
typedef SampleType_t DspSample_t;

#ifdef __cplusplus
}
#endif

#endif /* DSP_MCAL_TYPES_H */
