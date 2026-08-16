#ifndef BACK_COUNT_TYPES_H
#define BACK_COUNT_TYPES_H

#include "std_includes.h"
#include "back_count_const.h"


#define BACK_COUNT_COMMON_VARIABLES                  \
    char* name;                                      \
    uint8_t num;                                     \
    uint32_t count;                                  \
    uint32_t time_out_ms;                            \
    bool valid;

typedef struct {
    BACK_COUNT_COMMON_VARIABLES
}BackCountConfig_t;

typedef struct {
    BACK_COUNT_COMMON_VARIABLES
    bool init;
    BackCountState_t state;
    uint32_t off_time_ms;
    uint32_t on_time_ms;
    uint32_t spin;
}BackCountHandle_t;


#endif /* BACK_COUNT_TYPES_H */
