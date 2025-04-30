#ifndef SCAN_DIAG_H
#define SCAN_DIAG_H

#include "scan_types.h"

const char* ScanConfigToStr(const ScanConfig_t* const Config);
const char* ScanNodeToStr(const ScanHandle_t* const Node);
const char* ScanStateToStr(ScanState_t state);

#endif /* SCAN_DIAG_H  */
