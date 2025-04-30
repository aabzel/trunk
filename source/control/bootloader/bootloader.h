#ifndef BOOTLOADER_MCAL_H
#define BOOTLOADER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "bootloader_types.h"
#include "bootloader_config.h"
#ifdef HAS_BOOTLOADER_DIAG
#include "bootloader_diag.h"
#endif

bool bootloader_init(void);
bool bootloader_reboot(void);
bool bootloader_set_indicate(void);
bool bootloader_proc(void);
bool bootloader_try_app(void);
bool bootloader_erase_app(void);
bool bootloader_launch_app( BootCmd_t bootloader_cmd);


#ifdef __cplusplus
}
#endif

#endif /* BOOTLOADER_MCAL_H */
