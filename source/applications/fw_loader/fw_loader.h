#ifndef FW_LOADER_DRV_H
#define FW_LOADER_DRV_H


#include "std_includes.h"
#include "fw_loader_config.h"
#include "fw_loader_types.h"
#include "fw_loader_diag.h"

const FwLoaderConfig_t* FwLoaderGetConfig(uint8_t num);
bool FwLoaderIsValidConfig(const  FwLoaderConfig_t* const Config);
FwLoaderHandle_t* FwLoaderGetNode(uint8_t num);

bool fw_loader_mcal_init(void);
bool fw_loader_init_one(uint8_t num);
bool fw_loader_init_custom(void);

bool fw_loader_proc(void);
bool fw_loader_proc_one(uint8_t num);

bool fw_loader_jump(uint8_t num, uint32_t base_address);
bool fw_loader_download(uint8_t num);
bool fw_loader_ping(uint8_t num);
bool fw_loader_erase_chip(uint8_t num);
bool fw_loader_upload(uint8_t num, char* hex_file);
bool fw_loader_write(const uint8_t num,
                     const uint32_t relative_adress,
                     const uint8_t *const data,
                     const uint32_t size);

bool fw_loader_read(const uint8_t num,
                    const uint32_t relative_adress,
                    uint8_t *const data,
                    const uint32_t size);

#endif /* FW_LOADER_DRV_H */
