#ifndef BLACK_BOX_TYPES_H
#define BLACK_BOX_TYPES_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "black_box_const.h"
#include "black_box_dep.h"

#define BLACK_BOX_COMMON_VARIABLES                 \
    uint8_t num;                                   \
    bool valid;

typedef struct {
    BLACK_BOX_COMMON_VARIABLES
} BlackBoxConfig_t;

typedef struct {
    BLACK_BOX_COMMON_VARIABLES
} BlackBoxHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* BLACK_BOX_TYPES_H */
