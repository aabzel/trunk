#ifndef FW_LOADER_DRV_H
#define FW_LOADER_DRV_H


#include "std_includes.h"
#include "fw_loader_config.h"
#include "fw_loader_types.h"
#include "fw_loader_diag.h"

const FwLoaderConfig_t* FwLoaderGetConfig(uint8_t num);
FwLoaderHandle_t* FwLoaderGetNode(uint8_t num);
bool fw_loader_init_one(uint32_t num);
bool FwLoaderIsValidConfig(const  FwLoaderConfig_t* const Config);
bool fw_loader_mcal_init(void);
bool fw_loader_proc(void);
bool fw_loader_init_custom(void);
bool fw_loader_proc_one(uint32_t num);


#endif /* FW_LOADER_DRV_H */
