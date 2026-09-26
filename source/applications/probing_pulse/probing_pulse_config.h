#ifndef PROBING_PULSE_CONFIG_H
#define PROBING_PULSE_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "probing_pulse_types.h"
#include "probing_pulse_dep.h"

typedef enum{
    PROBING_PULSE_NUM_MONO,
    PROBING_PULSE_NUM_CHIRP,
    PROBING_PULSE_NUM_BARKER,
    PROBING_PULSE_NUM_M_SEQ,
}ProbingPulseLegalNums_t;

extern const ProbingPulseConfig_t ProbingPulseConfig[];
extern ProbingPulseHandle_t ProbingPulseInstance[];

uint32_t probing_pulse_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* PROBING_PULSE_CONFIG_H */
