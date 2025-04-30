#ifndef GPS_1BIT_TYPES_H
#define GPS_1BIT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gps_1bit_const.h"
#include "data_types.h"


#define GPS_COMMON_VARIABLES                 \
    uint8_t num;                             \
    bool valid;

typedef struct {
    GPS_COMMON_VARIABLES
}Gps1BitConfig_t;


typedef struct {
    GPS_COMMON_VARIABLES
}Gps1BitHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* GPS_TYPES_H  */
