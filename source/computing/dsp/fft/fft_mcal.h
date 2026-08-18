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

#define FFT_MAX_GARMONIC_CNT 250000U

bool fft_calc(const SampleType_t* const real_signal,
              uint32_t sample_cnt,
              double complex* const fft_out,
              double sampling_period_s,
              uint32_t max_garmonic_cnt);

bool ifft_calc(const double complex* const Spectrum,
               uint32_t number_of_harmonics,
               uint32_t sample_cnt,
               double complex* const x_signal);

#ifdef __cplusplus
}
#endif

#endif /* FFT_H */
