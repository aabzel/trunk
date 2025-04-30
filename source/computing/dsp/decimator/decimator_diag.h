#ifndef DECIMATOR_DIAG_H
#define DECIMATOR_DIAG_H

#include "decimator_types.h"

const char* DecimatorConfigToStr(const DecimatorConfig_t* const Config);
const char* DecimatorNodeToStr(const DecimatorHandle_t* const Node);
const char* DecimatorStateToStr(DecimatorState_t state);

#endif /* DECIMATOR_DIAG_H  */
