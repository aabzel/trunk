#ifndef LOCKSTEP_CONFIG_H
#define LOCKSTEP_CONFIG_H

#include "lockstep_types.h"
#include "std_includes.h"

extern const LockStepConfig_t LockStepConfig[];
extern LockStepHandle_t LockStepInstance[];

uint32_t lockstep_get_cnt(void);

#endif /*LOCKSTEP_CONFIG_H*/
