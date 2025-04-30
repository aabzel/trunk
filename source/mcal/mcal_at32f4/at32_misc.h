#ifndef AT32F4XX_MICS_H
#define AT32F4XX_MICS_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "at32_const.h"
#include "microcontroller_const.h"
#include "hal_diag.h"


#define _disable_interrupt_()
#define _enable_interrupt_()

#ifdef __cplusplus
extern "C" {
#endif


extern uint32_t critical_nesting_level;

confirm_state  OnOffToConfirmState(bool on_off) ;
bool isFromInterrupt(void);
//bool mcu_uid_show(void);
void enter_critical(void);
void exit_critical(void);
bool set_read_protection(void);

#ifdef __cplusplus
}
#endif

#endif /* AT32F4XX_MICS_H */
