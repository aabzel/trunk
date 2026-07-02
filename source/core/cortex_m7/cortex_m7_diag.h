#ifndef CORTEX_M7_DIAG_H
#define CORTEX_M7_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
//#include "core_cm7.h"
#include "microcontroller.h"

bool parse_control_reg(uint32_t controll_reg);
bool parse_faultmask_reg(uint32_t reg_val);
bool parse_basepri_reg(uint32_t reg_val);
bool print_vector_table(uint32_t vectors_table_base) ;
bool CortexM7_SCB_Diag(const SCB_Type* const SCBx);

#ifdef __cplusplus
}
#endif

#endif /* CORTEX_M7_DIAG_H */
