
#ifndef FIR_INT_CONFIG_H
#define FIR_INT_CONFIG_H

#include "std_includes.h"

#include "fir_int_types.h"
#include "fir_int_dep.h"

extern const FirIntConfig_t FirIntConfig[];
extern FirIntHandle_t FirIntInstance[];

uint32_t fir_int_get_cnt(void);

#endif /* FIR_INT_CONFIG_H */
