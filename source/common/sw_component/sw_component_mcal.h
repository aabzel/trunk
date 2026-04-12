#ifndef SW_COMPONENT_MCAL_H
#define SW_COMPONENT_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_component_config.h"
#include "sw_component_types.h"
#ifdef HAS_SW_COMPONENT_DIAG
#include "sw_component_diag.h"
#endif

/* API */
SwComponentHandle_t* SwComponentGetNode(uint8_t num);
const SwComponentConfig_t* SwComponentGetConfig(uint8_t num);
bool SwComponentIsValidConfig(const SwComponentConfig_t* const Config);

#ifdef HAS_SW_COMPONENT_CUSTOM
const SwComponentInfo_t* SwComponentGetInfo(uint8_t num);
#endif

bool sw_component_mcal_init(void);
bool sw_component_init_custom(void);
bool sw_component_init_common(const SwComponentConfig_t* const Config, SwComponentHandle_t* const Node);
bool sw_component_init_node(SwComponentHandle_t* const Node);
bool sw_component_init_one(uint8_t num);

bool sw_component_proc_one(uint8_t num);
bool sw_component_proc(void);

/*setters*/

/*getters*/
bool sw_component_raw_reg_diag(uint8_t i) ;

#ifdef __cplusplus
}
#endif

#endif /* SW_COMPONENT_MCAL_H */
