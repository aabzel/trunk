#ifndef DFT_H
#define DFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>
#include <stdbool.h>
#include <stdint.h>

#include "audio_types.h"
#include "dft_dep.h"
#include "dft_diag.h"
#include "dft_types.h"

/*Discrete Fourier Transform*/

/* double ft_find_freq(double complex* Spectrum, uint32_t len, double period_s); */
bool dft_calc(const SampleType_t* const x_signal, uint32_t sample_cnt, double complex* const Spectrum, double sampling_period_s);

bool idft_calc(const double complex* const Spectrum, uint32_t number_of_harmonics,
               uint32_t sample_cnt, double complex* const x_signal);

#ifdef __cplusplus
}
#endif

#endif /* DFT_H */
