#ifndef FIR_CONFIG_H
#define FIR_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "fir_types.h"
#include "fir_dep.h"

extern const FirConfig_t FirConfig[];
extern FirHandle_t FirInstance[];

uint32_t fir_get_cnt(void);

#endif /* FIR_CONFIG_H */
