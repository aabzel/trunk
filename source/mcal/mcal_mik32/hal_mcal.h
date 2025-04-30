#ifndef HAL_MCAL_H
#define HAL_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
//#include "macro_utils.h"
#include "sys_config.h"
#include "mik32_hal_def.h"

#define _disable_interrupt_()
#define _enable_interrupt_()


extern uint32_t critical_nesting_level;


bool MIK32_HalRetToRes(const HAL_StatusTypeDef ret);
bool hal_init(void);
bool isFromInterrupt(void);
void enter_critical(void);
void exit_critical(void);
bool set_read_protection(void);

#ifdef __cplusplus
}
#endif

#endif /* HAL_MCAL_H */
