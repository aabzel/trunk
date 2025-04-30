#ifndef PHASE_DETECTOR_DIAG_H
#define PHASE_DETECTOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "phase_detector_types.h"


const char* PhaseDetectorNodeToStr(const  PhaseDetectorHandle_t* const Node);
const char* PhaseDetectorConfigToStr(const  PhaseDetectorConfig_t* const Config);

bool PhaseDetectorDiagConfig(const PhaseDetectorConfig_t* const Config);
bool phase_detector_generate_graphviz(uint8_t num);
bool phase_detector_diag(uint8_t num);
bool phase_detector_expract_mem(uint8_t num, uint32_t index, double* const value);
bool phase_detector_diag_mem(uint8_t num);
bool phase_detector_diag_raw_mem(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* PHASE_DETECTOR_DIAG_H */
