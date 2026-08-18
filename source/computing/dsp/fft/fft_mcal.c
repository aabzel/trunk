#include "fft_mcal.h"

#include <complex.h>
#include <math.h>
#include <stdlib.h>

#include "float_diag.h"
#include "time_mcal.h"
#include "fft.h"
#include "log.h"
#include "std_includes.h"
#include "utils_math.h"

// Fast Fourier transform for real array without VLA in plain C with complex.h
// https://lloydrochester.com/post/c/example-fft/
// https://github.com/eugeneyuchunlin/fft-C

#if 0
double PI;
typedef double complex cplx;
// tsr fft+
static void fft_iteration(cplx buf[], cplx out[], int n, int step){
    if (step < n) {
        fft_iteration(out, buf, n, step * 2);
        fft_iteration(out + step, buf + step, n, step * 2);

        for (int i = 0; i < n; i += 2 * step) {
            cplx t = cexp(-I * PI * i / n) * out[i + step];
            buf[i / 2]     = out[i] + t;
            buf[(i + n)/2] = out[i] - t;
        }
    }
}
#endif



/*
 */
bool fft_calc(const SampleType_t* const realSignal,
              uint32_t sample_cnt,
              double complex* const fft_out,
              double sampling_period_s,
              uint32_t max_garmonic_cnt) {
    bool res = false;
    LOG_INFO(FFT, "N:%u", sample_cnt);
    uint32_t calc_cnt = 0;
    res = is_power_of_two(sample_cnt);
    if(res) {
        calc_cnt = sample_cnt;
    } else {
        calc_cnt = (uint32_t)pow(2.0, ceil(log2((double)sample_cnt)));
    }
    LOG_INFO(FFT, "N:%u,CalcN:%u", sample_cnt, calc_cnt);
    uint32_t start_ms = time_get_ms32();


    double complex* SignalComplex = (double complex*)malloc(sizeof(double complex) * sample_cnt);
    if(SignalComplex) {
        res = true;
    } else {
        res = false;
        LOG_ERROR(SONAR, "MallocErr,Need:%u", sample_cnt);
    }

    if(res) {
        res = true;
        uint32_t i = 0;
        // PI = atan2(1, 1) * 4;
        for(i = 0; i < calc_cnt; i++) {
            if(i < sample_cnt) {
                SignalComplex[i] = ((double)realSignal[i]) + 0.0 * I;
            } else {
                SignalComplex[i] = 0.0 + 0.0 * I;
            }
        }

        FFT_CALC(SignalComplex, fft_out, calc_cnt);

        uint32_t duration_ms = time_calc_duration_ms(start_ms);
        LOG_INFO(FFT, "CalcDuration:%s s", FloatToStr( MSEC_2_SEC(duration_ms),3)   );
    } else {
        res = false;
        LOG_ERROR(FFT, "MemErr,Need:%u,Max:%u", calc_cnt, FFT_MAX_SIZE);
    }

    return res;
}



/*
  sample_cnt - the number of signal values ​​measured over the period, as well as
  the number of decomposition components;
  number_of_harmonics -  number of harmonics under consideration
 */
bool ifft_calc(const double complex* const Spectrum,
               uint32_t number_of_harmonics,
               uint32_t sample_cnt,
               double complex* const x_signal) {
    bool res = false;
    LOG_INFO(IFFT, "CalcFFT,Signal:%u Sam,Harm:%u Harm", sample_cnt, number_of_harmonics);
    if(Spectrum) {
        if(x_signal) {
            if(sample_cnt) {
                res = true;
            }
        }
    }

    if(res) {
        uint32_t start_ms = time_get_ms32();
        IFFT_CALC(Spectrum, x_signal, sample_cnt);
        uint32_t duration_ms = time_calc_duration_ms(start_ms);
        LOG_INFO(IFFT, "CalcDuration:%s s", FloatToStr( MSEC_2_SEC(duration_ms),3)   );
    }
    return res;
}
