#ifndef SYSTICK_MCAL_H
#define SYSTICK_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "systick_config.h"
#include "systick_types.h"
#include "systick_isr.h"

#ifdef HAS_SYSTICK_DIAG
#include "systick_diag.h"
#endif  

#ifdef HAS_SYSTICK_CUSTOM
#include "systick_custom.h"
#endif /**/

SysTickHandle_t* SysTickGetNode(uint8_t num) ;
const SysTickConfig_t* SysTickGetConfig(uint8_t num) ;

bool systick_mcal_init(void);
bool systick_custom_init(void);

/*setters*/
bool systick_set_load(uint32_t new_load);
bool systick_mcal_stop(void);
bool systick_start(void);
bool systick_stop(void);
bool systick_ctrl(bool on_off);
bool systick_clksrc_set(const SysTickClkSrc_t clksrc);
/*getters*/
bool systick_is_run(void);
uint32_t systick_get_load(void);
uint32_t systick_get_ms(void);
uint32_t systick_cnt_get(void);
uint32_t systick_get_base_freq(void);
uint64_t systick_get_us(void);
SysTickClkSrc_t systick_source_get(void);


#ifdef __cplusplus
}
#endif

#endif // SYSTICK_MCAL_H
