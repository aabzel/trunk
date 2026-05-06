#ifndef SLIDING_INTEGRAL_DIAG_H
#define SLIDING_INTEGRAL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>

#include "std_includes.h"
#include "sliding_integral_types.h"

const char* SlidingIntegralNodeToStr(const SlidingIntegralHandle_t* const Node);
const char* SlidingIntegralConfigToStr(const SlidingIntegralConfig_t* const Config);

bool SlidingIntegralDiagConfig(const SlidingIntegralConfig_t* const Config);
bool sliding_integral_generate_graphviz(uint8_t num);
bool sliding_integral_diag(uint8_t num);
bool sliding_integral_expract_mem(uint8_t num, uint32_t index, double* const value);
bool sliding_integral_diag_mem(uint8_t num);
bool sliding_integral_node_generate_graphviz(SlidingIntegralHandle_t* Node, FILE* FilePtr, int x, int y, char* lText, double val) ;
bool sliding_integral_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SLIDING_INTEGRAL_DIAG_H */
