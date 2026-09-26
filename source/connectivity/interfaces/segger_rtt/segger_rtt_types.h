#ifndef SEGGER_RTT_TYPES_H
#define SEGGER_RTT_TYPES_H

#include "std_includes.h"
#include "segger_rtt_const.h"

#define SEGGER_RTT_COMMON_VARIABLES                    \
    char* name;                                        \
    uint8_t num;                                       \
    unsigned BufferIndex;                              \
    uint8_t* RxBuffer;                                 \
    unsigned buffer_size;                              \
    bool valid;

typedef struct {
    SEGGER_RTT_COMMON_VARIABLES
}SeggerRttConfig_t;

typedef struct {
    SEGGER_RTT_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}SeggerRttHandle_t;


#endif /* SEGGER_RTT_TYPES_H */
