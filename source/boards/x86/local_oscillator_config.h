#ifndef SDR_CONFIG_H
#define SDR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "gnss_types.h"

extern const LocalOscillatorConfig_t LocalOscillatorConfig[];
extern LocalOscillatorHandle_t LocalOscillatorInstance[];

uint32_t local_oscillator_get_cnt(void);

#endif /* SDR_CONFIG_H */
