#ifndef PROBING_PULSE_DIAG_H
#define PROBING_PULSE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "probing_pulse_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_PROBING_PULSE
#error "+HAS_PROBING_PULSE"
#endif

#ifndef HAS_PROBING_PULSE_DIAG
#error "+HAS_PROBING_PULSE_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool probing_pulse_diag(void);
bool probing_pulse_diag_one(uint8_t num);
bool probing_pulse_raw_reg_diag(uint8_t num);
const char* ProbingPulseToStr(ProbingPulseType_t probing_pulse) ;
const char* ProbingPulseConfigToStr(const ProbingPulseConfig_t* const Config);
const char* ProbingPulseNodeToStr(const ProbingPulseHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* PROBING_PULSE_DIAG_H  */
