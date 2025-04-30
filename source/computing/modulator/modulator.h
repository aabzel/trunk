#ifndef MODULATOR_H
#define MODULATOR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"

#include "audio_types.h"
#include "modulator_types.h"
#include "modulator_dep.h"

bool modulator_modulate(Modulator_t* instance,
const uint8_t* const raw_data, uint32_t data_size );

bool modulator_demodulate(Modulator_t instance,
const SampleType_t* const x_signal,
uint8_t* const raw_data, uint32_t * const data_size );

#ifdef __cplusplus
}
#endif

#endif /* MODULATOR_H */
