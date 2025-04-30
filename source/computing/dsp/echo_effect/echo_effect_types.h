#ifndef ECHO_EFFECT_ECHO_EFFECT_TYPES_H
#define ECHO_EFFECT_ECHO_EFFECT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "echo_effect_const.h"
#include "circular_buffer_word_types.h"

#define ECHO_EFFECT_COMMON_VARIABLES          \
    uint8_t num;                              \
    double scale;                             \
    char* name;                               \
    int16_t *inArray;                         \
    uint32_t capacity;                        \
    bool valid;

typedef struct {
    ECHO_EFFECT_COMMON_VARIABLES
}EchoEffectConfig_t;

typedef struct {
    ECHO_EFFECT_COMMON_VARIABLES
    CircularBufferWord_t CircularBuffer;
    int16_t numerator;
    int16_t denominator;
    bool init;
}EchoEffectHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* ECHO_EFFECT_ECHO_EFFECT_TYPES_H */
