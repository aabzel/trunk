#ifndef BOOT_MANAGER_DIAG_H
#define BOOT_MANAGER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "boot_manager_types.h"

const char* BootStrToStr( const BootManagerSrc_t boot_src);
bool BootManagerRegBootDiag(BootManagerRegBoot_t* const Reg);
bool boot_manager_diag(void);

#ifdef __cplusplus
}
#endif

#endif /* BOOT_MANAGER_DIAG_H */
