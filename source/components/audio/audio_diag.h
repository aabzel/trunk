#ifndef AUDIO_DIAG_H
#define AUDIO_DIAG_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "audio_types.h"

bool audio_print_sample(const SampleType_t* const sample, size_t size);
const char* SampleMode2Str(SampleMode_t sample_mode);

#endif /* AUDIO_DIAG_H */
