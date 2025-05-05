#ifndef FW_LOADER_DIAG_H
#define FW_LOADER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "fw_loader_types.h"

bool fw_loader_diag(void);
bool FwLoaderDiag(const FwLoaderHandle_t* const Node);
const char* FwLoaderDiag2Str(const FwLoaderHandle_t* const Node);
const char* FwLoaderConfigToStr(const FwLoaderConfig_t* const Config);

#ifdef __cplusplus
}
#endif

#endif /* FW_LOADER_DIAG_H */
