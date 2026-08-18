#ifndef RS2058_TYPES_H
#define RS2058_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "rs2058_const.h"
#include "gpio_types.h"

typedef struct {
    uint8_t num;
    Pad_t in;
    GpioLogicLevel_t  in_ll;
    Rs2058State_t state;
    char * in_wire_name;
    char * no_wire_name;
    char * nc_wire_name;
    char * com_wire_name;
    char * designator;
    bool valid;
}Rs2058Sw_t;

typedef struct{
    Rs2058Sw_t sw[2];
    bool valid;
    uint8_t num;
}Rs2058Config_t;

typedef struct{
    Rs2058Sw_t sw[2];
    bool valid;
    uint8_t num;
    bool init;
}Rs2058Item_t;

#endif /* RS2058_TYPES_H */
