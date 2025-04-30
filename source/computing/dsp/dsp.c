#include "dsp.h"

#include "log.h"
#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_IIR
#include "iir.h"
#endif
/*
 *
 */
uint32_t ft_find_freq(double complex* Spectrum, uint32_t len, double period_s, Spectr_t* const maxFreqInfo) {
    uint32_t i = 0;
    uint32_t max_garm_index = 0;
    double freq_range = 1.0 / period_s;
    LOG_INFO(DSP, "FindMaxFreq,Size:%u,SamplePeriod:%f S,%f Hz", len, period_s, freq_range);
    Spectr_t curFreqInfo = {0};
    Spectr_t CurMaxFreqInfo = {0};

    for(i = 0; i < len; i++) {
        curFreqInfo.frequency_hz = ((double)i) / (period_s * ((double)len));
        if(curFreqInfo.frequency_hz < (freq_range / 2.0)) {
            curFreqInfo.amplitude = cabs(Spectrum[i]);
            if(CurMaxFreqInfo.amplitude < curFreqInfo.amplitude) {
                if(0.001 < curFreqInfo.frequency_hz) {
                    max_garm_index = i;
                    CurMaxFreqInfo = curFreqInfo;
                    *maxFreqInfo = curFreqInfo;
                    LOG_DEBUG(DSP, "UpdateMax:s", DspMaxFreqToStr(&curFreqInfo));
                }
            }
        } else {
            break;
        }
    }
    *maxFreqInfo = CurMaxFreqInfo;
    LOG_INFO(DSP, "Max:%s", DspMaxFreqToStr(&CurMaxFreqInfo));
    return max_garm_index;
}

bool filter_proc_in_out(uint8_t num, DspFilterType_t filter_type, FilterSample_t x, FilterSample_t* const y) {
    bool res = false;
    LOG_DEBUG(DSP, "FILTER:%u,Type:%u", num, filter_type);
    switch(filter_type) {
    case DSP_FILTER_TYPE_FIR: {
#ifdef HAS_FIR
        res = fir_proc_in_out(num, x, y);
#endif
    } break;
    case DSP_FILTER_TYPE_IIR: {
#ifdef HAS_IIR
        res = iir_proc_in_out(num, (IirSample_t)x,(IirSample_t*) y);
#endif
    } break;
    default:
        break;
    }
    return res;
}

bool filter_synthesize(uint8_t num, DspFilterType_t filter_type, uint32_t filter_order,
                       double cutoff_frequency_hz, double sampling_frequency_hz) {
    bool res = false;
    switch(filter_type) {
    case DSP_FILTER_TYPE_FIR: {
#ifdef HAS_FIR
        res = fir_synthesize(num, filter_order, cutoff_frequency_hz, sampling_frequency_hz);
#endif
    } break;
    case DSP_FILTER_TYPE_IIR: {
#ifdef HAS_IIR
        res = iir_synthesize(num, filter_order, cutoff_frequency_hz, sampling_frequency_hz);
#endif
    } break;
    default:
        break;
    }
    return res;
}
