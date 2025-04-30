#ifndef SYS_AT32F413ZGJ6_H
#define SYS_AT32F413ZGJ6_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "sys_config.h"

#define _disable_interrupt_()
#define _enable_interrupt_()

#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t critical_nesting_level;

bool isFromInterrupt(void);
void enter_critical(void);
void exit_critical(void);
bool set_read_protection(void);

#ifdef __cplusplus
}
#endif

#endif /* SYS_AT32F413ZGJ6_H */
