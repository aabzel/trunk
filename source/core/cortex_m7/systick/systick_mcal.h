#ifndef SYSTICK_GENERAL_H
#define SYSTICK_GENERAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "systick_config.h"
#include "systick_types.h"

#ifdef HAS_SYSTICK_DIAG
#include "systick_diag.h"
#endif /* */

#ifdef HAS_SYSTICK_CUSTOM
#include "systick_custom.h"
#endif /*HAS_SYSTICK_CUSTOM*/

void SysTickIntHandler(void);
bool systick_mcal_init(void);

/*setters*/
bool systick_general_set_load(uint32_t new_load);
bool systick_mcal_stop(void);
bool systick_general_start(void);
bool systick_stop(void);
bool systick_start(void);

/*getters*/
bool systick_general_is_run(void);
uint32_t systick_general_get_load(void);
uint32_t systick_general_get_ms(void);
SysTickClkSrc_t systick_source_get(void);
uint64_t systick_general_get_us(void);
uint32_t systick_cnt_get(void);


#ifdef __cplusplus
}
#endif

#endif // SYSTICK_GENERAL_H
