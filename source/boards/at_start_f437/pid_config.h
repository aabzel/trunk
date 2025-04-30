#ifndef PID_CONFIG_H
#define PID_CONFIG_H

#include "pid_types.h"

typedef enum {
    PID_NUM_ADC_EXT_OUT1  =1, //ADC_EXT_OUT1 ADC_EXT1_IN
    PID_NUM_ADC_EXT_OUT2  =2, //ADC_EXT_OUT2 ADC_EXT2_IN
    PID_NUM_DIGIT_EXT_OUT2=3, //DIGIT_EXT_OUT2 DIGIT_EXT1_IN
    PID_NUM_DIGIT_EXT_OUT1=4, //DIGIT_EXT_OUT1 DIGIT_EXT2_IN

    PID_NUM_UNDEF = 0,
} Pid_TeraTestNums_t;

extern const PidConfig_t PidConfig[];
extern PidHandle_t PidInstance[];

uint32_t pid_get_cnt(void);

#endif /* PID_CONFIG_H  */
