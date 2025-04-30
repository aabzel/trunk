#ifndef DSP_H
#define DSP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <complex.h>

#ifdef HAS_AUDIO
#include "audio_types.h"
#endif
#include "dsp_diag.h"
#include "dsp_types.h"

uint32_t ft_find_freq(double complex* Spectrum, uint32_t len, double period_s,
                      Spectr_t* const max_garmonic);

bool filter_proc_in_out(uint8_t num, DspFilterType_t filter_type, FilterSample_t x, FilterSample_t *const y);

bool filter_synthesize(uint8_t num,
                       DspFilterType_t filter_type,
                       uint32_t order,
                       double cutoff_frequency_hz,
                       double sampling_frequency_hz);

#ifdef __cplusplus
}
#endif

#endif /* DSP_H */
