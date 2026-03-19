#ifndef TRNG_MCAL_TYPES_H
#define TRNG_MCAL_TYPES_H

#include "std_includes.h"
#include "trng_const.h"

#ifdef HAS_TRNG_CUSTOM
#include "trng_custom_types.h"
#else
#define TRNG_CUSTOM_VARIABLES
#endif

#define TRNG_COMMON_VARIABLES                          \
    char* name;                                        \
    uint8_t num;                                       \
    bool interrupt_on;                                 \
    bool valid;

typedef struct {
    TRNG_COMMON_VARIABLES
}tRngConfig_t;

typedef struct {
    TRNG_COMMON_VARIABLES
    TRNG_CUSTOM_VARIABLES
    bool init;
    uint8_t byte;
    uint16_t word;
    uint32_t dword;
    uint64_t qword;
    uint32_t spin;
}tRngHandle_t;


#endif /* TRNG_MCAL_TYPES_H */
