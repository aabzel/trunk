#ifndef ACCELEROMETER_DIAGNOSTIC_H
#define ACCELEROMETER_DIAGNOSTIC_H

#include "general_types.h"
#include "diag_dep.h"
#include "accelerometer_type.h"

#ifndef HAS_ACCELEROMETER_EHAL_DIAG
#error "+ HAS_ACCELEROMETER_DIAG"
#endif

const char* ACCEL_CalibDataToStr(ACCEL_CALIB_DATA* const CalibData);
const char* ACCEL_ConfigToStr(const ACCEL_CONFIG* const Config);
const char* ACCEL_NodeToStr(const ACCEL_HANDLE* const Node) ;

STD_RESULT ACCEL_Diag(void);
STD_RESULT ACCEL_DiagNode(ACCEL_HANDLE* const Node);
STD_RESULT ACCEL_DiagConfig(const ACCEL_CONFIG* const Config);

#endif /* ACCELEROMETER_MONO_DIAG_H  */
