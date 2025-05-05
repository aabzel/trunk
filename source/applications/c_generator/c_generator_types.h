#ifndef NOR_C_GENERATOR_TYPES_H
#define NOR_C_GENERATOR_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_types.h"
#include "c_generator_const.h"

#define C_GENERATOR_COMMON_VARIABLES         \
    bool valid;                                 \
    char filename[30];

typedef struct {
    C_GENERATOR_COMMON_VARIABLES
} cGeneratorConfig_t;

typedef struct {
    C_GENERATOR_COMMON_VARIABLES
    bool init;
    char letter_cur;
    char letter_prev;
    FuncNameParseState_t state;
    FuncNameParseInput_t input;
    uint32_t function_cnt;
    uint32_t line_num;
    uint32_t brace_cnt;
    uint32_t brace_open_cnt;
    uint32_t brace_close_cnt;

} cGeneratorHandle_t;

#endif /* NOR_C_GENERATOR_TYPES_H */
