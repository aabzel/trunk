#ifndef COMMON_CONST_H
#define COMMON_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SW_OFF = 0,
    SW_ON = 1,
    SW_UNDEF = 2,
}OnOff_t;

typedef enum {
    ST_DISABLE=0,
    ST_ENABLE=1,
    ST_UNDEF=2,
}State_t;

#ifdef __cplusplus
}
#endif

#endif /* COMMON_CONST_H */
