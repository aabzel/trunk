#ifndef CORRELATOR_TYPES_H
#define CORRELATOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "correlator_const.h"
#include "circular_buffer_word_types.h"

#define CORRELATOR_COMMON_VARIABLES            \
    CircularBufferWord_t* SignalA;             \
    CircularBufferWord_t* SignalB;             \
    uint32_t size;                             \
    uint32_t num;                              \
    char* name;                                \
    bool valid;

typedef struct {
    CORRELATOR_COMMON_VARIABLES
}CorrelatorConfig_t;

typedef struct {
    CORRELATOR_COMMON_VARIABLES
	int32_t correlation_result;
    bool init;
}CorrelatorHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* CORRELATOR_TYPES_H */
