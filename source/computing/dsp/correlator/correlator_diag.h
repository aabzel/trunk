#ifndef CORRELATOR_DIAG_H
#define CORRELATOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include  "correlator_types.h"

bool correlator_diag(uint8_t num);
const char* CorrelatorConfigToStr(const CorrelatorConfig_t* const Config);
const char* CorrelatorNodeToStr(const CorrelatorHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_DIAG_H */
