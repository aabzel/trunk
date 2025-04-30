#ifndef CORTEX_M4_DIAG_H
#define CORTEX_M4_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "microcontroller_drv.h"
#ifdef HAS_EHAL
#include "miscellaneous_ehal.h"
#endif

#ifdef HAS_CMSIS
//#include "core_cm4.h"
#endif
#include "cortex_m4_const.h"

const char* CortecM4CoProcAccessToStr(CoProcAccess_t access);
bool parse_control_reg(uint32_t controll_reg);
bool parse_faultmask_reg(uint32_t reg_val);
bool parse_basepri_reg(uint32_t reg_val);
bool cortex_m4_breakpoints(void);
#ifdef HAS_CMSIS
bool CortexM4ScbDiag(const SCB_Type* const Node);
#endif

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M4_DIAG_H */
