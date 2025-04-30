#ifndef FIR_DIAG_H
#define FIR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>

#include "std_includes.h"
#include "fir_types.h"


const char* FirNodeToStr(const  FirHandle_t* const Node);
const char* FirConfigToStr(const  FirConfig_t* const Config);

const char* FirModeToStr(FirMode_t mode);
bool FirDiagConfig(const FirConfig_t* const Config);
bool fir_generate_graphviz(uint8_t num);
bool fir_diag(uint8_t num);
bool fir_expract_mem(uint8_t num, uint32_t index, double* const value);
bool fir_diag_mem(uint8_t num);
bool fir_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* FIR_DIAG_H */
