#ifndef PID_CONFIG_H
#define PID_CONFIG_H

#include "pid_types.h"

typedef enum{
    PID_NUM_UNDEF = 0,
#ifdef HAS_LOCAL_OSCILATOR
    PID_NUM_LOC_OCS_PHASE,
#endif
    PID_NUM_SMOOTH_LAMP,
    PID_NUM_CNT,
}PidLegalNums_t;

extern const PidConfig_t PidConfig[];
extern PidHandle_t PidInstance[];

uint32_t pid_get_cnt(void);

#endif /* PID_CONFIG_H  */
