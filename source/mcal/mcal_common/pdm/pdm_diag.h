#ifndef PDM_DIAG_H
#define PDM_DIAG_H

#include <stdbool.h>

#include "pdm_types.h"

const char* PdmEdge2Str(PdmEdge_t edge);
bool pdm_calc_dft(uint8_t num);
bool pdm_diag(void);
bool pdm_diag_one(uint8_t num);
bool pdm_print_sample(uint8_t num);
bool PdmDiagConfig(const PdmConfig_t* const Config);
// bool PdmDiagNode(const PdmHandle_t* const Node);
const char* MicMode2Str(MicMode_t mode);

#endif /* PDM_DIAG_H */
