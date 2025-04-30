#include "dft_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"

const char* DftMaxFreqToStr(Spectr_t* const maxFreqInfo) {
    static char text[250] = "";
    strcpy(text, "");
    snprintf(text, sizeof(text), "%sFreq:%s_Hz,", text, DoubleToStr(maxFreqInfo->frequency_hz));
    snprintf(text, sizeof(text), "%sAmp:%s_PCM", text, DoubleToStr(maxFreqInfo->amplitude));
    return text;
}
