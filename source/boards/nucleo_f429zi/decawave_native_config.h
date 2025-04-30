
#ifndef DECAWAVE_NATIVE_CONFIG_H
#define DECAWAVE_NATIVE_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "decawave_native_types.h"

#ifndef HAS_DECAWAVE_NATIVE
#error " +HAS_DECAWAVE_NATIVE"
#endif

extern const DecaWaveNativeConfig_t DecaWaveNativeConfig[];
extern DecaWaveNativeHandle_t DecaWaveNativeInstance[];

uint32_t decawave_native_get_cnt(void);

#endif /* DECAWAVE_NATIVE_CONFIG_H */
