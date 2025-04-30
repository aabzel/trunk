#ifndef SYSTICK_CORE_MCAL_H
#define SYSTICK_CORE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "systick_general_config.h"
#include "systick_types.h"

#ifdef HAS_SYSTICK_CUSTOM
#include "systick_custom.h"
#endif /*HAS_SYSTICK_CUSTOM*/

bool systick_init(void);
void SysTickIntHandler(void);
bool systick_general_set_load(uint32_t new_load);
bool systick_custom_init(void);
bool systick_ctrl(bool on_off);
bool systick_general_is_run(void);
bool systick_general_stop(void);
bool systick_general_start(void);
bool systick_general_init(void);
bool systick_disable(void);
uint32_t systick_general_get_load(void);
uint32_t systick_general_get_ms(void);
uint64_t systick_general_get_us(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_CORE_MCAL_H
