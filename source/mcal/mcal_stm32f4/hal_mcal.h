#ifndef HAL_MCAL_H
#define HAL_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "macro_utils.h"
#include "sys_config.h"

#ifdef HAS_DIAG
#include "hal_diag.h"
#endif

#define _disable_interrupt_()
#define _enable_interrupt_()

extern uint32_t critical_nesting_level;

bool hal_init(void);
bool HAL_retToRes( const HAL_StatusTypeDef ret);
bool isFromInterrupt(void);
bool set_read_protection(void);
void enter_critical(void);
void exit_critical(void);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_MCAL_H */
