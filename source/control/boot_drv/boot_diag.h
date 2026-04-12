#ifndef BOOT_DIAG_H
#define BOOT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "boot_types.h"

bool boot_diag(void);
const char* BootNodeToStr(const BootHandle_t* const Node) ;
const char* BootConfigToStr(const BootConfig_t* const Config) ;
const char* BootCmdToStr(const BootCmd_t boot_cmd);
const char* StorageBootCmdToStr(const void* const data );
char* AppSize2str(uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_DIAG_H */
