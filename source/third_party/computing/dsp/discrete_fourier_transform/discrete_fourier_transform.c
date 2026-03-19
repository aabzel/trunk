#include "discrete_fourier_transform.h"

#include <complex.h>
#include <math.h> // for cos sin



//******************************************************************************
//! [Description of DFT_Calc]
//!
//! \note       Calc discrete Fourier transform
//!             See https://ru.dsplib.org/content/dft/dft.html
//!
//! \param[in]  signal - array of signal samples
//! \param[in]  numberOfSamples - number Of Samples
//! \param[in]  parameterOne - [description of parameterOne]
//! \param[in]  signalDurationSec - [description of parameterOne]
//! \param[out] dftOut - [description of parameterTwo]
//!
//! \return     [Description of return value]
//******************************************************************************
STD_RESULT DFT_Calc(const SAMPLE_TYPE* const signal,
                    U32 numberOfSamples, double complex* const dftOut,
                    double signalDurationSec) {
	STD_RESULT res = RESULT_NOT_OK;
    if(signal) {
        if(dftOut) {
            res = RESULT_OK;
            U32 k = 0;
            for(k = 0; k < numberOfSamples; k++) {
                dftOut[k] = 0.0 + 0.0 * I;
                U32 n = 0;
                for(n = 0; n < numberOfSamples; n++) {
                    dftOut[k] += ((double)signal[n]) * (cos(TWO_PI_VAL * ((double)k * n) / ((double)numberOfSamples)) -
                                                        sin(TWO_PI_VAL * ((double)k * n) / ((double)numberOfSamples)) * I);
                }

                dftOut[k] = 2.0 * dftOut[k] / ((double)numberOfSamples);
            }
        }
    }
    return res;
}

//******************************************************************************
//! [Description of DFT_FindStrongestFreqHz]
//!
//! \note       Find the strongest frequency in spectr
//!
//! \param[in]  spectrum - input discrete spectrum
//! \param[in]  len - frequency range
//! \param[in]  oneSampleDurationSec -  duration of one sample in seconds
//! \param[in]  len - [description of parameterOne]
//! \param[out] maxSpectrum - max Spectrum Node [freq + its amp ]
//!
//! \return     the strongest frequency in spectrum
//******************************************************************************
double DFT_FindStrongestFreqHz(const double complex* const spectrum, U32 len,
        double oneSampleDurationSec,
		Spectr_t* const maxSpectrum) {
    U32 i = 0;
    double freqRange = 1.0 / oneSampleDurationSec;
    Spectr_t curSpectr = {0};
    Spectr_t maxSpectr = {0};

    for(i = 0; i < len; i++) {
        curSpectr.freq = ((double)i) / (oneSampleDurationSec * ((double)len));
        if(curSpectr.freq < (freqRange / 2.0)) {
            curSpectr.amplitude = cabs(spectrum[i]);
            if(maxSpectr.amplitude < curSpectr.amplitude) {
                if(0.001 < curSpectr.freq) {
                    maxSpectr = curSpectr;
                    *maxSpectrum = curSpectr;
                }
            }
        } else {
            break;
        }
    }
    return maxSpectr.freq;
}
