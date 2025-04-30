#ifndef DSP_DIAG_H
#define DSP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dsp_types.h"

const char* DspFilterTypeToStr(DspFilterType_t filter_type) ;
const char* DspMaxFreqToStr(Spectr_t* const maxFreqInfo);

#ifdef __cplusplus
}
#endif

#endif /* DSP_DIAG_H */
