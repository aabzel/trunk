#ifndef GNSS_DIAG_H
#define GNSS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "gps.h"

const char* GpsSatToStr(const GpsSat_t* const Node);
const char* PrnInfoToStr(const PrnInfo_t* const PrnInfo);
const char* GpsNodeToStr(const GpsHandle_t* const Node);
const char* GpsConfigToStr(const GpsConfig_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* GNSS_DIAG_H */
