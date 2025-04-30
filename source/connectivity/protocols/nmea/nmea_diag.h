#ifndef NMEA_DIAG_H
#define NMEA_DIAG_H

#include "std_includes.h"
#include "nmea_types.h"

const char* NmeaPosModeToStd(PositionMode_t pos_mode);
const char* NmeaNodeToStr(const NmeaHandle_t *const Node);
const char* NmeaNodeMainToStr(const NmeaHandle_t *const Node);

bool nmea_data(uint8_t num);
bool nmea_diag(uint8_t num);
bool nmea_messages(uint8_t num);

#endif /* NMEA_DIAG_H */
