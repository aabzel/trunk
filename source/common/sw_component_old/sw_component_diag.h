#ifndef SW_COMPONENT_DIAG_H
#define SW_COMPONENT_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_component_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SW_COMPONENT
#error "+HAS_SW_COMPONENT"
#endif /*HAS_SW_COMPONENT*/

#ifndef HAS_SW_COMPONENT_DIAG
#error "+HAS_SW_COMPONENT_DIAG"
#endif /*HAS_DIAG_SW_COMPONENT*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool sw_component_diag(void);
const char* SwComponentConfigToStr(const SwComponentConfig_t* const Config);
const char* SwComponentNodeToStr(const SwComponentHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* SW_COMPONENT_DIAG_H  */
