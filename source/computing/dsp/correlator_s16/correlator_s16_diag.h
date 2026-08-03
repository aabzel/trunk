#ifndef CORRELATOR_S16_DIAG_H
#define CORRELATOR_S16_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>

#include "std_includes.h"
#include "correlator_s16_types.h"


const char* CorrelatorS16NodeToStr(const  CorrelatorS16Handle_t* const Node);
const char* CorrelatorS16ConfigToStr(const  CorrelatorS16Config_t* const Config);


bool CorrelatorS16DiagConfig(const CorrelatorS16Config_t* const Config);
bool correlator_s16_generate_graphviz(uint8_t num);
bool correlator_s16_diag(uint8_t num);
bool correlator_s16_expract_mem(uint8_t num, uint32_t index, double* const value);
bool correlator_s16_diag_mem(uint8_t num);
bool correlator_s16_node_generate_graphviz(CorrelatorS16Handle_t* Node, FILE* FilePtr, int x, int y, char* lText, double val) ;
bool correlator_s16_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_S16_DIAG_H */
