
#ifndef NMEA_CONFIG_H
#define NMEA_CONFIG_H

#include <std_includes.h>

#include "nmea_types.h"

#ifndef HAS_NMEA
#error "+HAS_NMEA"
#endif

extern const NmeaConfig_t NmeaConfig[];
extern NmeaHandle_t NmeaInstance[];

uint32_t nmea_get_cnt(void);

#endif /* NMEA_CONFIG_H */
