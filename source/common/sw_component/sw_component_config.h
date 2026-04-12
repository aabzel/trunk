#ifndef SW_COMPONENT_CONFIG_H
#define SW_COMPONENT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_component_types.h"
#include "sw_component_dep.h"

extern const SwComponentConfig_t SwComponentConfig[];
extern SwComponentHandle_t SwComponentInstance[];

uint32_t sw_component_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* SW_COMPONENT_CONFIG_H */
