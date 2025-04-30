#include "complex_math.h"


bool complex_array_mux(const double complex *const RecSpectrum,
                       const double complex *const PulseSpectrum,
                       double complex *const MuxSpectrum,
                       uint32_t max_sample_cnt) {
    bool res = false;
    if (RecSpectrum) {
        if (PulseSpectrum) {
            if (MuxSpectrum) {
                if (max_sample_cnt) {
                    uint32_t i = 0;
                    for (i = 0; i < max_sample_cnt; i++) {
                        MuxSpectrum[i] = RecSpectrum[i] * PulseSpectrum[i];
                    }
                    res = true;
                }
            }
        }
    }
    return res;
}
