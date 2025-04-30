#ifndef COMPLEX_MATH_H
#define COMPLEX_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>

#include "std_includes.h"

bool complex_array_mux(const double complex* const RecSpectrum,
                       const double complex* const PulseSpectrum,
                       double complex* const MuxSpectrum,
                       uint32_t max_sample_cnt);




#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_MATH_H */
