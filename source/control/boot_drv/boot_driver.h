#ifndef BOOT_DRV_H
#define BOOT_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "boot_types.h"
#include "boot_diag.h"
#include "boot_config.h"

//extern BootData_t BootData;

bool boot_reboot(void);
bool bool_proc_start_error(const uint32_t reset_handler) ;
bool boot_jump_to_code(uint32_t app_start_address);
bool boot_check_reset_handler(const uint32_t app_start_address,
                              uint32_t *const reset_handler);
#ifdef HAS_ARM
bool boot_jump_to_code_arm(const uint32_t app_start_address );
#endif

#ifdef __cplusplus
}
#endif

#endif /* BOOT_DRV_H */
