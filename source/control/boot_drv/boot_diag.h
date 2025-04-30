#ifndef BOOT_DIAG_H
#define BOOT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "boot_const.h"

bool boot_diag(void);
const char* BootCmdToStr(const BootCmd_t boot_cmd);
char* AppSize2str(uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_DIAG_H */
