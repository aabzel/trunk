#ifndef FFT_H
#define FFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>

#include "audio_types.h"
#include "std_includes.h"
#include "fft_types.h"
#include "dsp_types.h"


bool fft_calc(const SampleType_t* const real_signal, uint32_t sample_cnt,
              double complex* const fft_out, double t_big) ;

#ifdef __cplusplus
}
#endif

#endif /* FFT_H */
