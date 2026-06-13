#ifndef SMOOTH_LAMP_MCAL_H
#define SMOOTH_LAMP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "smooth_lamp_config.h"
#include "smooth_lamp_types.h"

#ifdef HAS_SMOOTH_LAMP_DIAG
#include "smooth_lamp_diag.h"
#endif

/* API */
SmoothLampHandle_t* SmoothLampGetNode(uint8_t num);
const SmoothLampConfig_t* SmoothLampGetConfig(uint8_t num);
bool SmoothLampIsValidConfig(const SmoothLampConfig_t* const Config);

#ifdef HAS_SMOOTH_LAMP_CUSTOM
const SmoothLampInfo_t* SmoothLampGetInfo(uint8_t num);
#endif

bool smooth_lamp_mcal_init(void);
bool smooth_lamp_init_custom(void);
bool smooth_lamp_init_one(uint8_t num);
bool smooth_lamp_init_common(const SmoothLampConfig_t* const Config,
                             SmoothLampHandle_t* const Node);

bool smooth_lamp_proc_one(uint8_t num);
bool smooth_lamp_proc(void);

float calc_climax2(SmoothLampHandle_t* Node) ;
float calc_decay2(SmoothLampHandle_t* Node);
float calc_decay1(SmoothLampHandle_t* Node);

/*setters*/
bool smooth_lamp_logistic_shift(uint8_t num,float logistic_shift);
bool smooth_lamp_limit_down(uint8_t num, float limit_down);
bool smooth_lamp_limit_up(uint8_t num, float up_limit);
bool smooth_lamp_mult(uint8_t num, float mult);
bool smooth_lamp_ctrl(uint8_t num, bool on_off);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* SMOOTH_LAMP_MCAL_H */
