#ifndef TIME_GENERAL_TYPES_H
#define TIME_GENERAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "time_const.h"

#ifdef HAS_MATH
#include "math_const.h"
#endif

typedef struct {
    double start;
    double end;
}TimeStampSec_t;

typedef struct {
    uint32_t sec;
    uint32_t digit;
    uint32_t fractional_cnt;
#ifdef HAS_MATH
    DigitPart_t part;
#endif
    double digit_f;
    char prev_char;
}DurationFsm_t;

#define TIME_COMMON_VARIABLES    \
    uint8_t num;                 \
    bool valid;                  \
    TimeSource_t time_source;

typedef struct {
    TIME_COMMON_VARIABLES
} TimeConfig_t ;

typedef struct {
    TIME_COMMON_VARIABLES
    bool init_done;
}TimeHandle_t;




#ifdef __cplusplus
}
#endif

#endif /* TIME_GENERAL_TYPES_H */
