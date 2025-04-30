#ifndef CLOCK_DIVIDER_CLOCK_DIVIDER_TYPES_H
#define CLOCK_DIVIDER_CLOCK_DIVIDER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "clock_divider_const.h"

#define CLOCK_DIVIDER_COMMON_VARIABLES          \
    double amp;                                 \
    uint32_t divider;                           \
    uint8_t num;                                \
    uint8_t schmitt_trigger_num;                \
    char* name;                                 \
    bool valid;

typedef struct {
    CLOCK_DIVIDER_COMMON_VARIABLES
    double cur_out;
    uint32_t counter;
    uint32_t sample_cnt;
}ClockDividerHandle_t;

typedef struct {
    CLOCK_DIVIDER_COMMON_VARIABLES
}ClockDividerConfig_t;

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_DIVIDER_CLOCK_DIVIDER_TYPES_H */
