#ifndef PROBING_PULSE_MCAL_H
#define PROBING_PULSE_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "probing_pulse_config.h"
#include "probing_pulse_types.h"

#ifdef HAS_PROBING_PULSE_DIAG
#include "probing_pulse_diag.h"
#endif

/* API */
ProbingPulseHandle_t* ProbingPulseGetNode(uint8_t num);
const ProbingPulseConfig_t* ProbingPulseGetConfig(uint8_t num);
bool ProbingPulseIsValidConfig(const ProbingPulseConfig_t* const Config);

#ifdef HAS_PROBING_PULSE_CUSTOM
const ProbingPulseInfo_t* ProbingPulseGetInfo(uint8_t num);
#endif

bool probing_pulse_mcal_init(void);
bool probing_pulse_init_custom(void);
bool probing_pulse_init_common(const ProbingPulseConfig_t* const Config, ProbingPulseHandle_t* const Node);
bool probing_pulse_init_node(ProbingPulseHandle_t* const Node);
bool probing_pulse_init_one(uint8_t num);

bool probing_pulse_proc_one(uint8_t num);
bool probing_pulse_proc(void);

/*setters*/

/*getters*/
bool probing_pulse_is_valid_num(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* PROBING_PULSE_MCAL_H */
