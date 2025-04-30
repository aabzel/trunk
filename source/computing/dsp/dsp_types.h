#ifndef DSP_TYPES_H
#define DSP_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "dsp_const.h"
#include "bit_types.h"

typedef struct {
    double frequency_hz;
    double amplitude;
}Spectr_t;

typedef union {
    uint8_t u8[3];
    int8_t s8[3];
    BitField24_t bits24;
} Sample24bit_t;


typedef float FilterSample_t;
typedef int8_t Gain_t;

//#ifdef HAS_PC
//typedef double SampleType_t;
//#else

#ifdef HAS_PCM_16_BIT
typedef int16_t SampleType_t;
#endif

#ifdef HAS_PCM_32_BIT
typedef int32_t SampleType_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* DSP_TYPES_H */
