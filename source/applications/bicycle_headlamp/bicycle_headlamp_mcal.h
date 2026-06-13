#ifndef BICYCLE_HEADLAMP_MCAL_H
#define BICYCLE_HEADLAMP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bicycle_headlamp_config.h"
#include "bicycle_headlamp_types.h"

#ifdef HAS_BICYCLE_HEADLAMP_DIAG
#include "bicycle_headlamp_diag.h"
#endif

/* API */
BicycleHeadLampHandle_t* BicycleHeadLampGetNode(uint8_t num);
const BicycleHeadLampConfig_t* BicycleHeadLampGetConfig(uint8_t num);
bool BicycleHeadLampIsValidConfig(const BicycleHeadLampConfig_t* const Config);

bool bicycle_headlamp_mcal_init(void);
bool bicycle_headlamp_init_custom(void);
bool bicycle_headlamp_init_common(const BicycleHeadLampConfig_t* const Config, BicycleHeadLampHandle_t* const Node);
bool bicycle_headlamp_init_node(BicycleHeadLampHandle_t* const Node);
bool bicycle_headlamp_init_one(uint8_t num);

bool bicycle_headlamp_proc_one(uint8_t num);
bool bicycle_headlamp_proc(void);

/*setters*/

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* BICYCLE_HEADLAMP_MCAL_H */
