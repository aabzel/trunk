#ifndef SCAN_TYPES_H
#define SCAN_TYPES_H

#include <std_includes.h>

#include "scan_const.h"
#include "sensitivity_const.h"


#define SCAN_COMMON_VARIABLES                         \
    uint32_t num;                                     \
    uint32_t sample_freq_hz;                          \
    float threshold;                                  \
    float timeout_s;                                  \
    char* name;                                       \
    bool valid;

typedef struct {
    SCAN_COMMON_VARIABLES
} ScanConfig_t;

typedef struct {
    SCAN_COMMON_VARIABLES
    bool init;
    ScanState_t state;
    ScanInput_t input;
    ScanAction_t action;
    ScanState_t prev_state;
    float value_in;
    float up_time_s;
} ScanHandle_t;

#endif /* SCAN_TYPES_H  */
