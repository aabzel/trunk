#ifndef DC_CUT_FILTER_TYPES_H
#define DC_CUT_FILTER_TYPES_H

#include "std_includes.h"
#include "dc_cut_filter_const.h"

#define DC_CUT_FILTER_COMMON_VARIABLES                 \
    char* name;                                        \
    float alfa;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    DC_CUT_FILTER_COMMON_VARIABLES
}DcCutFilterConfig_t;

typedef struct {
    DC_CUT_FILTER_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    int32_t a_n_1;
    int32_t denominator;
    int32_t numerator;
}DcCutFilterHandle_t;


#endif /* DC_CUT_FILTER_TYPES_H */
