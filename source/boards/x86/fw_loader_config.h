#ifndef FW_LOADER_CONFIG_H
#define FW_LOADER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fw_loader_types.h"

extern const FwLoaderConfig_t FwLoaderConfig[];
extern FwLoaderHandle_t FwLoaderInstance[];

uint32_t fw_loader_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*FW_LOADER_CONFIG_H*/
