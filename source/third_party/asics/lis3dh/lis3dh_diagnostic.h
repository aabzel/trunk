#ifndef LIS3DH_DIAGNOSTIC_H
#define LIS3DH_DIAGNOSTIC_H


#include "diag_dep.h"
#include "lis3dh_type.h"
#include "platform.h"

#ifndef HAS_LIS3DH_DIAGNOSTIC
#error "+HAS_LIS3DH_DIAG"
#endif /*HAS_DIAG_LIS3DH*/

const char* LIS3DH_AccelerationToStr(const LIS3DH_ACCELERATION* const Acceleration);
const char* LIS3DH_ConfigurationToStr(const LIS3DH_CONFIGURATION* const Config);
const char* LIS3DH_NodeToStr(const LIS3DH_HANDLE* const Node);
const char* LIS3DH_RegAddrToName(LIS3DH_REGISTER_ADDR addr);
const char* LIS3DH_OpModeToStr(LIS3DH_OPERATION_MODE opMode);
STD_RESULT LIS3DH_AdcDiag(void);
STD_RESULT LIS3DH_RegDiag(LIS3DH_REGISTER_ADDR addr, U8 value);
STD_RESULT LIS3DH_DiagLowLevel(U8 num, const char* const keyWord);
STD_RESULT LIS3DH_DiagHighLevel(U8 num);
STD_RESULT LIS3DH_Diag(void);
STD_RESULT LIS3DH_DiagPll(U8 num);
STD_RESULT LIS3DH_DiadRegMap(U8 num, char* keyWord1, char* keyWord2);


#endif /* LIS3DH_DIAG_H  */
