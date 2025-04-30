#ifndef FM_TUNER_TYPES_H
#define FM_TUNER_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "data_types.h"

typedef struct {
    double fm_freq_mhz;
    const char* name;
    uint16_t id;
    bool rds;
}FmStationInfo_t;


#endif /* FM_TUNER_TYPES_H */
