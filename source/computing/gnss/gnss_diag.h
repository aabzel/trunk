#ifndef GNSS_DIAG_H
#define GNSS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "gnss_utils.h"

bool print_wgs84_coordinate(Wgs84Coordinate_t Wgs84Coordinate, bool one_line) ;
bool print_coordinate(char* prefix, GnssCoordinate_t coordinate, bool one_line);
bool print_velocity(GnssVelocity_t velocity);
const char* SignalTypeToStr(SignalType_t sig_type); // SDR
char* coordinate2str(void* value);
const char* GnssCoordinateToStr(const GnssCoordinate_t* const coordinate);
char* BearingDeg2Str(double value);
const char*  EscortInfoToStr(const GnssEscortInfo_t* const Node);
const char* SdrCorrToStr(const SdrCorrRes_t* const Node);
const char* SdrEplToStr(const SdrEPL_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* GNSS_DIAG_H */
