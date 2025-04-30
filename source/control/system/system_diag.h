#ifndef SYSTEM_DIAG_H
#define SYSTEM_DIAG_H

#include "sys_constants.h"
#include "system.h"
#include "system_types.h"

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_SYSTEM_DIAG
#warning "+HAS_SYSTEM_DIAG"
#endif

//bool sys_available_interfaces(void);

const char* ProgType2str(BuildType_t fw_type);
const char* Facility2Str(facility_t facility);
const char* facility2str_lut(facility_t facility);
uint16_t facility_max_name(void);
bool system_diag(void);

#endif /* SYSTEM_DIAG_H  */
