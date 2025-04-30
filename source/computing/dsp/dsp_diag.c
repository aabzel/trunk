#include "dsp_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"

const char* DspMaxFreqToStr(Spectr_t* const maxFreqInfo) {
    static char text[250] = "";
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sFreq:%s_Hz,", text, DoubleToStr(maxFreqInfo->frequency_hz));
    snprintf(text, sizeof(text), "%sAmp:%s_PCM", text, DoubleToStr(maxFreqInfo->amplitude));
    return text;
}

const char* DspFilterTypeToStr(DspFilterType_t filter_type) {
    char* name = "?";
    switch(filter_type) {
    case DSP_FILTER_TYPE_FIR:
        name = "FIR";
        break;
    case DSP_FILTER_TYPE_IIR:
        name = "IIR";
        break;
    default:
        break;
    }
    return name;
}
