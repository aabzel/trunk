#ifndef JUMPER_CODE_TYPES_H
#define JUMPER_CODE_TYPES_H

#include "std_includes.h"
#include "jumper_code_const.h"
#include "gpio_types.h"

typedef struct {
    uint32_t code;
    bool valid;
    Pad_t set;
    Pad_t get;
}JumperCodePosition_t;


#define JUMPER_CODE_COMMON_VARIABLES                  \
    JumperCodePosition_t* Position;                   \
    char* name;                                       \
    uint32_t position_cnt;                            \
    uint8_t num;                                      \
    bool valid;


typedef struct {
    JUMPER_CODE_COMMON_VARIABLES
}JumperCodeConfig_t;

typedef struct {
    JUMPER_CODE_COMMON_VARIABLES
    bool init;
    uint32_t code;
    uint32_t spin;
}JumperCodeHandle_t;


#endif /* JUMPER_CODE_TYPES_H */
