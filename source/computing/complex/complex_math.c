#include "complex_math.h"

#include <complex.h>

#include "log.h"

bool complex_array_mux(const double complex* const Spectrum1,
                       const double complex* const Spectrum2,
                       double complex* const MuxSpectrum,
                       uint32_t size) {
    bool res = false;
    LOG_WARNING(SYS, "complex_array_mux,size:%u", size);
    if(Spectrum1) {
        if(Spectrum2) {
            if(MuxSpectrum) {
                if(size) {
                    uint32_t i = 0;
                    for(i = 0; i < size; i++) {
                        MuxSpectrum[i] = Spectrum1[i] * Spectrum2[i];
                    }
                    res = true;
                }
            }
        }
    }
    return res;
}

bool complex_array_conjugate( double complex* const inSpectrum, uint32_t size) {
    bool res = false;
    LOG_WARNING(SYS, "Conjugate,size:%u", size);
    if(inSpectrum) {
        if(size) {
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                inSpectrum[i] = conj(inSpectrum[i] );
            }
            res = true;
        }
    }
    return res;
}
