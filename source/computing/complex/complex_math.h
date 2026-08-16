#ifndef COMPLEX_MATH_H
#define COMPLEX_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>

#include "std_includes.h"
#include "complex_diag.h"

bool complex_array_mux(const double complex* const Spectrum1,
        const double complex* const Spectrum2,
        double complex* const MuxSpectrum,
        uint32_t max_sample_cnt);

bool complex_array_conjugate( double complex* const PulseSpectrum, uint32_t max_sample_cnt);

#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_MATH_H */
