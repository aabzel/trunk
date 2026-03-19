#ifndef DISCRETE_FOURIER_TRANSFORM_H
#define DISCRETE_FOURIER_TRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>

#include "general_types.h"
#include "i2s_drv_types.h"
#include "discrete_fourier_transform_types.h"


double DFT_FindStrongestFreqHz(const double complex* const spectrum, U32 len,
		double oneSampleDurationSec, Spectr_t* const curSpectr);

// Discrete Fourier Transform
STD_RESULT DFT_Calc(const SAMPLE_TYPE* const x_signal, U32 numberOfSamples,
		double complex* const dftOut, double signalDurationSec);

#ifdef __cplusplus
}
#endif

#endif /* DISCRETE_FOURIER_TRANSFORM_H */
