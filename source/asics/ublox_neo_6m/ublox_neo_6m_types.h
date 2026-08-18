#ifndef UBLOX_NEO_6M_TYPES_H
#define UBLOX_NEO_6M_TYPES_H

#include <time.h>

#include "ublox_neo_6m_const.h"
#include "gnss_types.h"

#define UBLOX_NEO_6M_COMMON_VARIABLES    \
    uint8_t num;                         \
    uint8_t uart_num;                    \
    uint16_t rate_hz;                    \
    bool valid;

typedef struct  {
    UBLOX_NEO_6M_COMMON_VARIABLES
} uBloxNeo6mConfig_t;

typedef struct  {
    UBLOX_NEO_6M_COMMON_VARIABLES
    struct tm time_date;
    GnssCoordinate_t coordinate;
    double alt_base;
    int8_t time_zone;
    bool init;
} uBloxNeo6mHandle_t;

#endif /* UBLOX_NEO_6M_TYPES_H  */
