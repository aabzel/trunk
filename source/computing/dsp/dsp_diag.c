#include "dsp_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"

const char* DspFilterTypeToStr(DspFilterType_t filter_type) {
    char* name = "?";
    switch(filter_type) {
        case DSP_FILTER_TYPE_FIR:        name = "FIR";        break;
        case DSP_FILTER_TYPE_IIR:        name = "IIR";        break;
        case DSP_FILTER_TYPE_SAMPLE_SUM: name = "Sum";        break;
        default:        break;
    }
    return name;
}

const char* DspMaxFreqToStr(Spectr_t* const maxFreqInfo) {
    static char temp[250] = "";
    strcpy(temp, "");
    snprintf(temp, sizeof(temp), "%sFreq:%s_Hz,", temp, DoubleToStr(maxFreqInfo->frequency_hz));
    snprintf(temp, sizeof(temp), "%sAmp:%s_PCM", temp, DoubleToStr(maxFreqInfo->amplitude));
    return temp;
}
