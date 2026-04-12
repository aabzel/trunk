#ifndef CORE_DIAG_H
#define CORE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "core_types.h"

#ifdef HAS_CORTEX_M4
#include "cortex_m4_diag.h"
#endif

#ifdef HAS_CORTEX_M33
#include "cortex_m33_diag.h"
#endif

#ifdef HAS_CORTEX_M7
#include "cortex_m7_diag.h"
#endif

#ifdef HAS_CORTEX_M4
#ifdef HAS_CORTEX_M33
#error  "Core contradiction!"
#endif
#endif

#ifdef HAS_CORTEX_M7
#ifdef HAS_CORTEX_M33
#error  "Core contradiction!"
#endif
#endif

#ifdef HAS_CORTEX_M4
#ifdef HAS_CORTEX_M7
#error  "Core contradiction!"
#endif
#endif

const char* CortexFpuTypeToStr(const CortexFpu_t fpu_type) ;
const char* CoreConfigToStr(const CoreConfig_t* const Config);
const char* CoreNodeToStr(const CoreHandle_t* const Node);

bool print_vector_table(const uint32_t vectors_table_base) ;
bool core_stack_print(const uint8_t num);
bool core_diag_stack_mem(void);
bool core_diag(void);
bool core_diag_stack_usage(const uint8_t num, const FloatFixPoint_t* stack_used) ;

#ifdef __cplusplus
}
#endif

#endif /* CORE_DIAG_H */
