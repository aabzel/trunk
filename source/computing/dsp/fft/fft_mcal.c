#include "fft_mcal.h"

#include <complex.h>
#include <math.h>

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

bool fft_calc(const SampleType_t* const real_signal, uint32_t sample_cnt, double complex* const fft_out, double t_big) {
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
    if(calc_cnt < FFT_MAX_SIZE) {
        double complex fft_in[FFT_MAX_SIZE] = {0};
        res = true;
        uint32_t i = 0;
        // PI = atan2(1, 1) * 4;
        for(i = 0; i < calc_cnt; i++) {
            if(i < sample_cnt) {
                fft_in[i] = ((double)real_signal[i]) + 0.0 * I;
            } else {
                fft_in[i] = 0.0 + 0.0 * I;
            }
        }

        FFT_CALC(fft_in, fft_out, calc_cnt);
    } else {
        res = false;
        LOG_ERROR(FFT, "MemErr,Need:%u,Max:%u", calc_cnt, FFT_MAX_SIZE);
    }

    return res;
}
