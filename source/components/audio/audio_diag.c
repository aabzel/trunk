#include "audio_diag.h"

#include <stdio.h>
#include <string.h>

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

const char* SampleMode2Str(DspSampleMode_t sample_mode) {
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

const char* AudioStereoSample16bitToStr(const AudioStereoSample16bit_t* const Node) {
    static char temp[80] = {0};
    if(Node) {
        memset(temp, 0, sizeof(temp));
        snprintf(temp, sizeof(temp), "%sL:%d,", temp, Node->left);
        snprintf(temp, sizeof(temp), "%sR:%d,", temp, Node->right);
    }
    return temp;
}
