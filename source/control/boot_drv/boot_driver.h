#ifndef BOOT_MCAL_H
#define BOOT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "boot_types.h"
#include "boot_config.h"

#ifdef HAS_RATIONAL_NUM
#include "rational_num_types.h"
#endif

#ifdef HAS_BOOT_DIAG
#include "boot_diag.h"
#endif

BootHandle_t* BootGetNode(uint8_t num);
const BootConfig_t* BootGetConfig(uint8_t num) ;

bool boot_proc(void);
bool boot_proc_one(uint8_t num) ;
bool boot_init_one(uint8_t num) ;
bool boot_mcal_init(void);

/*getters*/
bool boot_stack_paint(const uint8_t num, FloatFixPoint_t * const stack_used);
uint32_t boot_stack_top_addr_get(const uint8_t num) ;
bool boot_seek_vector_table(const uint32_t mem_start,const uint32_t size);
bool boot_check_reset_handler(const uint32_t app_start_address,
                              uint32_t *const reset_handler);

/*setters*/
bool boot_reboot(void);
bool bool_proc_start_error(const uint32_t reset_handler) ;
bool boot_jump_to_code(uint32_t app_start_address);

#ifdef HAS_ARM
bool boot_jump_to_code_arm(const uint32_t app_start_address);
#endif

#ifdef __cplusplus
}
#endif

#endif /* BOOT_MCAL_H */
