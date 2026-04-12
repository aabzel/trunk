#ifndef HIST_FILTER_TYPES_H
#define HIST_FILTER_TYPES_H

#include "std_includes.h"
#include "hist_filter_const.h"
#include "schmitt_trigger_types.h"

typedef union {
    uint8_t byte;
    struct {
        uint8_t tgrigger0 :1;  /**/
        uint8_t tgrigger1 :1;  /**/
        uint8_t tgrigger2 :1;  /**/
        uint8_t tgrigger3 :1;  /**/
        uint8_t res :4;
    };
} HistFilterState_t;

#define HIST_FILTER_COMMON_VARIABLES                                                  \
    char* name;                                                                       \
    uint8_t num;                                                                      \
    SchmittTriggerShortConfig_t SchmittTriggerShortConfig[4];                         \
    bool valid;

typedef struct {
    HIST_FILTER_COMMON_VARIABLES
}HistFilterConfig_t;

typedef struct {
    HIST_FILTER_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    HistFilterState_t state;
    SchmittTriggerHandle_t SchmittTrigger[4];
}HistFilterHandle_t;


#endif /* HIST_FILTER_TYPES_H */
