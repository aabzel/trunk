#ifndef PROBING_PULSE_CONST_H
#define PROBING_PULSE_CONST_H

#include "time_mcal.h"
#include "probing_pulse_dep.h"

#define PROBING_PULSE_VERSION 1

typedef enum {
    PROBING_PULSE_TYPE_UNDEF,
    PROBING_PULSE_TYPE_MONO,
    PROBING_PULSE_TYPE_CHIRP,
    PROBING_PULSE_TYPE_BAKER13,
    PROBING_PULSE_TYPE_M_SEQ,
    PROBING_PULSE_CNT,
}ProbingPulseType_t;

#endif /* PROBING_PULSE_CONST_H */
