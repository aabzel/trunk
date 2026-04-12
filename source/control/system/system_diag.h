#ifndef SYSTEM_DIAG_H
#define SYSTEM_DIAG_H

#include "system.h"

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_SYSTEM_DIAG
#warning "+HAS_SYSTEM_DIAG"
#endif

//bool sys_available_interfaces(void);

const char* ProgType2str(const BuildType_t fw_type);
const char* FacilityToStr(const facility_t facility);
const char* facility2str_lut(const facility_t facility);
uint16_t facility_max_name(void);
bool system_diag(void);

#endif /* SYSTEM_DIAG_H  */
