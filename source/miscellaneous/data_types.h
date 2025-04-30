#ifndef EXTRA_DATA_TYPES_H
#define EXTRA_DATA_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "data_const.h"

#ifdef HAS_BIT_UTILS
#include "bit_types.h"
#endif



typedef struct {
    uint64_t cur;
    uint64_t min;
    uint64_t max;
} U64Value_t;

typedef struct {
    uint64_t cur;
    uint64_t prev;
} MindValU64_t;

typedef struct {
    uint32_t cur;
    uint32_t min;
    uint32_t max;
} U32Value_t;

typedef struct {
    uint16_t min;
    uint16_t cur;
    uint16_t max;
} U16Value_t;

typedef struct {
    double cur;
    double min;
    double max;
} DoubleValue_t;

typedef struct {
    float cur;
    float min;
    float max;
} FloatValue_t;

typedef struct {
    uint8_t min;
    uint8_t cur;
    uint8_t max;
} U8Value_t;


typedef union {
    uint64_t u64;
    int64_t s64;
    double d64;
    uint32_t u32[2];
    int32_t s32[2];
    float f32[2];
    uint16_t u16[4];
    int16_t s16[4];
    uint8_t u8[8];
    int8_t s8[8];
#ifdef HAS_UTILS_EXT
    BitField64_t bits64;
#endif
} Type64Union_t;

typedef union {
    uint32_t u32;
    int32_t s32;
    float f32;
    uint16_t u16[2];
    int16_t s16[2];
    uint8_t u8[4];
    int8_t s8[4];
#ifdef HAS_UTILS_EXT
    BitField32_t bits32;
#endif
} Type32Union_t;

typedef union {
    uint8_t u8[3];
    int8_t s8[3];
#ifdef HAS_UTILS_EXT
    BitField24_t bits24;
#endif
} Type24Union_t;

typedef union {
    int16_t s16;
    uint16_t u16;
    uint8_t u8[2];
    int8_t s8[2];
} U16_bit_t;

typedef union {
    uint8_t u8;
    int8_t s8;
} U8_bit_t;

typedef union {
    uint16_t u16;
    int16_t s16;
    uint8_t u8[2];
    int8_t s8[2];
#ifdef HAS_UTILS_EXT
    BitField16_t bits16;
#endif
} Type16Union_t;

typedef union {
    uint32_t u32;
    int32_t s32;
    float f32;
    uint16_t u16[2];
    int16_t s16[2];
    uint8_t u8[4];
    int8_t s8[4];
} U32_bit_t;

typedef union {
    uint64_t u64;
    int64_t s64;
    uint32_t u32[2];
    int32_t s32[2];
    float d64;
    float f32[2];
    uint16_t u16[4];
    int16_t s16[4];
    uint8_t u8[8];
    int8_t s8[8];
} U64_bit_t;

typedef struct {
    uint16_t mantissa : 11;
    uint16_t sign : 1;
    uint16_t exponent : 4;
} __attribute__((packed)) TypeHighSnrFmt_t;

typedef union {
    uint16_t u16;
    struct {
        uint16_t mantissa : 11;
        uint16_t sign : 1;
        uint16_t exponent : 4;
    } __attribute__((packed));
} __attribute__((packed)) TypeHighSnr_t;

typedef union {
    uint8_t u8;
    int8_t s8;
#ifdef HAS_UTILS_EXT
    BitField8_t bits8;
#endif
    struct {
        uint8_t nibble_l : 4;
        uint8_t nibble_h : 4;
    };
} Type8Union_t;

#ifdef __cplusplus
}
#endif

#endif /* EXTRA_DATA_TYPES_H */
