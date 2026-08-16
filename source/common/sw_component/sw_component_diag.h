#ifndef SW_COMPONENT_DIAG_H
#define SW_COMPONENT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_component_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SW_COMPONENT
#error "+HAS_SW_COMPONENT"
#endif

#ifndef HAS_SW_COMPONENT_DIAG
#error "+HAS_SW_COMPONENT_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool sw_component_diag(void);
bool sw_component_diag_one(uint8_t num);
bool sw_component_raw_reg_diag(uint8_t num);
const char* SwComponentConfigToStr(const SwComponentConfig_t* const Config);
const char* SwComponentNodeToStr(const SwComponentHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SW_COMPONENT_DIAG_H  */
