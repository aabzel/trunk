#include "audio_diag.h"

#include "audio_types.h"
#include "log_utils.h"

bool audio_print_sample(const SampleType_t* const sample, size_t size) {
    bool res = false;
    uint32_t i = 0;
    if(sample) {
        cli_printf("[");
        for(i = 0; i < size; i++) {
            res = true;
            if(i == (size - 1)) {
                cli_printf("%d", sample[i]);
            } else {
                cli_printf("%d, ", sample[i]);
            }
        }
        cli_printf("]" CRLF);
    }
    return res;
}

const char* SampleMode2Str(SampleMode_t sample_mode) {
    const char* name = "";
    switch(sample_mode) {
    case SAMPLE_MODE_MONO:
        name = "Mono";
        break;
    case SAMPLE_MODE_STEREO:
        name = "Stereo";
        break;
    default:
        break;
    }
    return name;
}
