#ifndef MAX98357_TYPES_H
#define MAX98357_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "max98357_const.h"
#include "gpio_types.h"

#define MAX98357_COMMON_VARIABLES \
    uint8_t i2s_num; \
    uint8_t dac_num; \
    Pad_t shut_down_pad;  \
    uint8_t num;  \
    bool valid;

typedef struct{
    MAX98357_COMMON_VARIABLES
}Max98357Config_t;

typedef struct{
    MAX98357_COMMON_VARIABLES
    bool init_done;
}Max98357Handle_t;


#endif /* MAX98357_TYPES_H */
