#ifndef AUDIO_DIAG_H
#define AUDIO_DIAG_H

#include <stddef.h>

#include "std_includes.h"
#include "audio_types.h"

bool audio_print_sample(const SampleType_t* const sample, size_t size);
const char* SampleMode2Str(DspSampleMode_t sample_mode);

#endif /* AUDIO_DIAG_H */
