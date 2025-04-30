#ifndef SCHMITT_TRIGGER_TYPES__H
#define SCHMITT_TRIGGER_TYPES__H

#include <stdbool.h>
#include <stdint.h>

#include "schmitt_trigger_const.h"
#include "sensitivity_const.h"

typedef bool (*SchmittTriggerIsrHandler_t)(void);

#define SCHMITT_TRIGGER_COMMON_VARIABLES                         \
    uint32_t num;                                                \
    double hysteresis;                                           \
    double switching_value;                                      \
    SchmittTriggerIsrHandler_t up_call_back;                     \
    SchmittTriggerIsrHandler_t down_call_back;                   \
    char* name;                                                  \
    Units_t units;                                               \
    bool valid;

#define SCHMITT_TRIGGER_NAME_SIZE 20
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
    double value;
} SchmittTriggerHandle_t;

#endif /* SCHMITT_TRIGGER_TYPES__H  */
