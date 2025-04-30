#ifndef SWD_MCAL_TYPES_H
#define SWD_MCAL_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "data_utils.h"
#include "swd_const.h"
#include "swd_custom_types.h"
#include "sys_config.h"

#define SWD_COMMON_VARIABLES     \
    uint32_t baud_rate;          \
    bool valid;                  \
    uint8_t num;

typedef struct {
    SWD_COMMON_VARIABLES
    char *name;
}SwdConfig_t;

typedef struct {
    SWD_COMMON_VARIABLES
    SWD_CUSTOM_VARIABLES
} SwdHandle_t;

#endif /* SWD_MCAL_TYPES_H */
