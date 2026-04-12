#ifndef SCHMITT_TRIGGER_DIAG_H
#define SCHMITT_TRIGGER_DIAG_H

#include "schmitt_trigger_types.h"

const char* SchmittTriggerShortConfigToStr(const SchmittTriggerShortConfig_t* const Config);
const char* SchmittTriggerNodeToStr(const SchmittTriggerHandle_t* const Node);
const char* SchmittTriggerStateToStr(SchmittTriggerState_t state);

#endif /* SCHMITT_TRIGGER_DIAG_H  */
