#include "dft.h"

#include <complex.h>
#include <math.h>

#include "debug_info.h"
#include "dsp_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "std_includes.h"
#include "time_mcal.h"

#ifdef HAS_WATCHDOG
#include "watchdog_mcal.h"
#endif
/*
 * See https://ru.dsplib.org/content/dft/dft.html
 */

void dft_calc_v2(complex double in[], complex double out[], int sample_cnt, uint32_t max_garmonic_cnt) {
    double pi2_div_size = 2 * M_PI / sample_cnt;
    for(int k = 0; k < max_garmonic_cnt; ++k) {
        complex double sum = 0;
        double angle = pi2_div_size * k;
        for(int n = 0; n < sample_cnt; ++n) {
            sum += in[n] * (cos(angle * n) - I * sin(angle * n));
        }
        out[k] = sum;
    }
}

uint32_t dft_freq_to_garmonic(const double freq_hz, const double measure_interval_s) {
    uint32_t garmonic_num =(uint32_t)  ( freq_hz * measure_interval_s);
    LOG_INFO(DFT, "Freq:%f Hz,measureT:%f s,GarmonicNum:%u", freq_hz, measure_interval_s,garmonic_num);
    return garmonic_num;
}

/*
  signal - input signal array
  sample_cnt - sample quantity
  Spectrum - output Spectrum
  sampling_period_s - duration of one sample
  max_garmonic_cnt - the number of harmonics to be calculated

  It may take a very long time to calculate!
 */
bool dft_calc(const SampleType_t* const signal, uint32_t sample_cnt, double complex* const Spectrum,
              double sampling_period_s, uint32_t max_garmonic_cnt) {
    bool res = false;
    uint32_t start_ms = time_get_ms32();
    double measure_interval_s = ((double)sample_cnt) * sampling_period_s;
    LOG_WARNING(DFT, "N:%u Sam,SampleTimeS:%f s,T:%f s,MaxGarmonic:%u", sample_cnt, sampling_period_s, measure_interval_s, max_garmonic_cnt);
    if(signal) {
        if(Spectrum) {
            res = true;
            uint32_t k = 0;
            for(k = 0; k < max_garmonic_cnt; k++) {
                double cur_freq_hz = 0.0;
#ifdef HAS_WATCHDOG
                watchdog_proc();
#endif
                cur_freq_hz = ((double)k) / measure_interval_s;
                Spectrum[k] = 0.0 + 0.0 * I;
                uint32_t n = 0;
                for(n = 0; n < sample_cnt; n++) {
                    double signal_complex_n = ((double)signal[n])+0.0*I;
                    Spectrum[k] += ((double)signal_complex_n) * (cos(TWO_PI_VAL * ((double)k * n) / ((double)sample_cnt)) -
                                                                 sin(TWO_PI_VAL * ((double)k * n) / ((double)sample_cnt)) * I);
                }
                // Spectrum[k] *= 1.0 / ( ( (double)sample_cnt )  * (measure_interval_s));

                Spectrum[k] = 2.0 * Spectrum[k] / ((double)sample_cnt);
                LOG_DEBUG(DFT, "%u,Freq:%f Hz,(%6.3f)+j*(%6.3f)", k, cur_freq_hz, creal(Spectrum[k]),
                          cimag(Spectrum[k]));

                diag_progress_log(k, max_garmonic_cnt, 500, "Dft");
            }
        } else {
            LOG_ERROR(DFT, "ResErr");
        }
    } else {
        LOG_ERROR(DFT, "SignalErr");
    }
    uint32_t duration_ms = time_calc_duration_ms(start_ms);
    LOG_INFO(DFT, "CalcDuration:%s s", DoubleToStr(MSEC_2_SEC(duration_ms)));
    return res;
}

/*
  sample_cnt - the number of signal values ​​measured over the period, as well as
  the number of decomposition components;
  number_of_harmonics -  number of harmonics under consideration
 */
bool idft_calc(const double complex* const Spectrum, uint32_t number_of_harmonics, uint32_t sample_cnt,
               double complex* const x_signal) {
    bool res = false;
    LOG_INFO(IDFT, "CalcIDFT,Signal:%u Sam,Harm:%u Harm", sample_cnt, number_of_harmonics);
    if(Spectrum) {
        if(x_signal) {
            if(sample_cnt) {
                res = true;
            }
        }
    }

    if(res) {
        uint32_t start_ms = time_get_ms32();
        double inv_n = 1.0 / ((double)sample_cnt);
        uint32_t s = 0;
        for(s = 0; s < sample_cnt; s++) {
            double complex signal_n = 0.0;
            uint32_t m = 0;
            for(m = 0; m < number_of_harmonics; m++) {
                double phase_rad = (TWO_PI_VAL * ((double)(m * s))) / sample_cnt;
                double complex exponents = cos(phase_rad) + sin(phase_rad)*I;// ?
                signal_n += (Spectrum[m] * exponents);
            }
            x_signal[s] = inv_n * signal_n;
            diag_progress_log(s, sample_cnt, 250,"idft");
            res = true;
        }
        uint32_t duration_ms = time_calc_duration_ms(start_ms);
        LOG_INFO(IDFT, "CalcDuration:%s s", DoubleToStr(MSEC_2_SEC(duration_ms)));
    }
    return res;
}
