
#ifndef FIR_DIAG_H
#define FIR_INT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "fir_int_types.h"


const char* FirIntNodeToStr(const  FirIntHandle_t* const Node);

bool FirIntDiagConfig(const FirIntConfig_t* const Config);
bool fir_int_generate_graphviz(uint8_t num);
bool fir_int_diag(uint8_t num);
bool fir_int_expract_mem(uint8_t num, CircularBufferIndex_t index, double* const value);
bool fir_int_diag_mem(uint8_t num);
bool fir_int_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* FIR_DIAG_H */
