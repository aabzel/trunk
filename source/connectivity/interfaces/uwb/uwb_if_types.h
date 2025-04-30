#ifndef UWB_IF_TYPES_H
#define UWB_IF_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "uwb_if_const.h"
#include "data_types.h"

typedef struct {
    uint8_t num;
    IdStatus_t status;
    uint16_t id;
    DoubleValue_t range_m;
    bool valid;
    double ant_delay_m;
}UwbIdInfo_t;

#endif /* UWB_IF_TYPES_H  */
