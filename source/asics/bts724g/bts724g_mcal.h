#ifndef BTS724G_MCAL_H
#define BTS724G_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "bts724g_config.h"
#include "bts724g_types.h"

#ifdef HAS_BTS724G_DIAG
#include "bts724g_diag.h"
#endif

/* API */
Bts724gHandle_t* Bts724gGetNode(uint8_t num);
const Bts724gConfig_t* Bts724gGetConfig(uint8_t num);
bool Bts724gIsValidConfig(const Bts724gConfig_t* const Config);

#ifdef HAS_BTS724G_CUSTOM
const Bts724gInfo_t* Bts724gGetInfo(uint8_t num);
#endif

bool bts724g_mcal_init(void);
bool bts724g_init_custom(void);
bool bts724g_init_common(const Bts724gConfig_t* const Config, Bts724gHandle_t* const Node);
bool bts724g_init_node(Bts724gHandle_t* const Node);
bool bts724g_init_one(uint8_t num);

bool bts724g_proc_one(uint8_t num);
bool bts724g_proc(void);

/*setters*/
bool bts724g_frequency_set(uint8_t num, float frequency_hz);
bool bts724g_duty_set(uint8_t num, float duty_cycle);
bool bts724g_set(uint8_t num, bool on_off);

/*getters*/
bool bts724g_frequency_get(uint8_t num, float * const  frequency_hz);
bool bts724g_duty_get(uint8_t num, float * const duty_cycle);
bool bts724g_effective_get(const uint8_t num);
bool bts724g_state_get(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* BTS724G_MCAL_H */
