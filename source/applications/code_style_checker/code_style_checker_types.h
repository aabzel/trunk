#ifndef NOR_CODE_STYLE_CHECKER_TYPES_H
#define NOR_CODE_STYLE_CHECKER_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_types.h"
#include "code_style_checker_const.h"

#define CODE_STYLE_CHECKER_COMMON_VARIABLES         \
    bool valid;                                 \
    char filename[30];

typedef struct {
    CODE_STYLE_CHECKER_COMMON_VARIABLES
} CodeStyleCheckerConfig_t;

typedef struct {
    CODE_STYLE_CHECKER_COMMON_VARIABLES
    bool init;

} CodeStyleCheckerHandle_t;

#endif /* NOR_CODE_STYLE_CHECKER_TYPES_H */
