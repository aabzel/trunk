#ifndef CORRELATOR_NAIV_S16_DIAG_H
#define CORRELATOR_NAIV_S16_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>

#include "std_includes.h"
#include "correlator_naiv_s16_types.h"

const char* CorrelatorNaivS16NodeToStr(const  CorrelatorNaivS16Handle_t* const Node);
const char* CorrelatorNaivS16ConfigToStr(const  CorrelatorNaivS16Config_t* const Config);

bool CorrelatorNaivS16DiagConfig(const CorrelatorNaivS16Config_t* const Config);
bool correlator_naiv_s16_generate_graphviz(uint8_t num);
bool correlator_naiv_s16_diag(uint8_t num);
bool correlator_naiv_s16_expract_mem(uint8_t num, uint32_t index, int16_t* const value);
bool correlator_naiv_s16_diag_mem(uint8_t num);
bool correlator_naiv_s16_node_generate_graphviz(CorrelatorNaivS16Handle_t* Node, FILE* FilePtr, int x, int y, char* lText, double val) ;
bool correlator_naiv_s16_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_NAIV_S16_DIAG_H */
