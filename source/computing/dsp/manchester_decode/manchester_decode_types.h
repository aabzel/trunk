#ifndef MANCHESTER_DECODE_TYPES_H
#define MANCHESTER_DECODE_TYPES_H

#include "std_includes.h"
#include "manchester_decode_const.h"

#define MANCHESTER_DECODE_COMMON_VARIABLES             \
    char* name;                                        \
    uint8_t num;                                       \
    bool valid;

typedef struct {
    MANCHESTER_DECODE_COMMON_VARIABLES
}ManchesterDecodeConfig_t;

typedef struct {
    MANCHESTER_DECODE_COMMON_VARIABLES
    bool init;
    ManchesterDecodeState_t state;
    ManchesterDecodeState_t prev_state;
    ManchesterDecodeAction_t out;
    uint8_t rx_byte;
    uint32_t rx_cnt;
    uint32_t error_cnt;
    uint32_t cur_flow;
    uint32_t max_flow;
    int32_t rx_cnt_phase;
    uint32_t spin;
}ManchesterDecodeHandle_t;


#endif /* MANCHESTER_DECODE_TYPES_H */
