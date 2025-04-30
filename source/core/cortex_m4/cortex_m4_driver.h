#ifndef CORTEX_M4_DRV_H
#define CORTEX_M4_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cortex_m4_types.h"
#include "cortex_m4_diag.h"


bool cortex_m4_breakpoints_reset(void);
bool cortex_m4_breakpoint_set(uint8_t num, uint32_t address);
bool cortex_m4_exceptions(bool status);
bool cortex_m4_exceptions_nmi(bool status);
bool cortex_m4_coproc_access_set(uint8_t cp_num, CoProcAccess_t access_mode);
bool cortex_m4_coproc_access_get(uint8_t cp_num, CoProcAccess_t* const access_mode);
bool cortex_m4_init_isr_vector(void);
bool cortex_m4_reboot(void);
bool cortex_m4_is_interrupt(void);
bool cortex_m4_set_vector_table(uint32_t start_address);
bool cortex_m4_set_sp(StackPointerSel_t sp);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M4_DRV_H */
