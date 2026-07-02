#ifndef CORTEX_M7_DRV_H
#define CORTEX_M7_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "cortex_m7_types.h"
#include "cortex_m7_diag.h"

bool cortex_m7_init_isr_vector(void);
bool cortex_m7_is_interrupt(void);
bool cortex_m7_set_vector_table(uint32_t start_address);
bool cortex_m7_exceptions(bool status);
bool cortex_m7_set_sp(StackPointerSel_t sp);
bool cortex_m7_exceptions_nmi(bool status);
bool cortex_m7_reboot(void);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M7_DRV_H */
