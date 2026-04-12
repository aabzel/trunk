#ifndef SCHMITT_TRIGGER_TYPES__H
#define SCHMITT_TRIGGER_TYPES__H

#include "std_includes.h"
#include "schmitt_trigger_const.h"
#include "sensitivity_const.h"

typedef bool (*SchmittTriggerIsrHandler_t)(void);

#define SCHMITT_TRIGGER_CONFIG_VARIABLES                         \
    uint32_t num;                                                \
    float up_val;                                               \
    float down_val;                                             \
    float hysteresis;                                           \
    float switching_value;

#define SCHMITT_TRIGGER_COMMON_VARIABLES                         \
    SCHMITT_TRIGGER_CONFIG_VARIABLES                             \
    SchmittTriggerIsrHandler_t up_call_back;                     \
    SchmittTriggerIsrHandler_t down_call_back;                   \
    char* name;                                                  \
    Units_t units;                                               \
    bool valid;

typedef struct {
    SCHMITT_TRIGGER_CONFIG_VARIABLES
} SchmittTriggerShortConfig_t;


typedef struct {
    SCHMITT_TRIGGER_COMMON_VARIABLES
} SchmittTriggerConfig_t;

typedef struct {
    SCHMITT_TRIGGER_COMMON_VARIABLES
    bool init;
    SchmittTriggerState_t state;
    SchmittTriggerState_t prev_state;
    uint32_t up_handler_cnt;
    uint32_t down_handler_cnt;
    float value;
} SchmittTriggerHandle_t;

#endif /* SCHMITT_TRIGGER_TYPES__H  */
