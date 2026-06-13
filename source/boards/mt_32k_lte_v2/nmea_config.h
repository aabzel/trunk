#ifndef NMEA_CONFIG_H
#define NMEA_CONFIG_H

#include "nmea_types.h"

extern const NmeaConfig_t NmeaConfig[];
extern NmeaHandle_t NmeaInstance[];

uint32_t nmea_get_cnt(void);

#endif /* NMEA_CONFIG_H */
