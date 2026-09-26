#ifndef X86XX_MICS_H
#define X86XX_MICS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "macro_utils.h"
#include "x86x_const.h"
#include "microcontroller_const.h"
#include "hal_diag.h"
#include "sys_constants.h"


#define _disable_interrupt_()
#define _enable_interrupt_()

typedef struct{
    uint32_t ret;
    char* name;
    bool valid;
}Fc73StatusInfo_t;

extern uint32_t critical_nesting_level;

#ifdef HAS_LOG
bool log_fc73_ret(const facility_t facility, uint32_t ret, const char* const in_text) ;
#endif

const char* RetToStr(uint32_t ret);
bool microcontroller_init(void);
bool Fc7300xSdkStatusToRes(uint32_t ret);
bool isFromInterrupt(void);
void enter_critical(void);
void exit_critical(void);
bool set_read_protection(void);

#ifdef __cplusplus
}
#endif

#endif /* X86XX_MICS_H */
