#ifndef LIS3DH_DIAG_H
#define LIS3DH_DIAG_H

#include "std_includes.h"
#include "diag_dep.h"
#include "lis3dh_types.h"
#include "asics_types.h"

#ifndef HAS_LIS3DH_DIAG
#error "+HAS_LIS3DH_DIAG"
#endif /*HAS_DIAG_LIS3DH*/

const char* Lis3dhAccelerationToStr(const Lis3dhAcceleration_t* const Acceleration);
const char* Lis3dhConfigToStr(const Lis3dhConfig_t* const Config);
const char* Lis3dhNodeToStr(const Lis3dhHandle_t* const Node);
const char* Lis3dhRegAddrToName(Lis3dhRegAddr_t addr);
const char* Lis3dhOpModeToStr(Lis3dhOperationMode_t operation_mode);

bool Lis3dhRegDiag(Lis3dhRegAddr_t addr, uint8_t  value);
bool lis3dh_diag_low_level(uint8_t num, const char* const key_word);
bool lis3dh_diag_high_level(uint8_t num);
bool lis3dh_diag(void);
bool lis3dh_diag_pll(uint8_t num);
bool lis3dh_reg_hazy(uint8_t num);
bool lis3dh_reg_map_hidden_diag(uint8_t num);
bool lis3dh_reg_map_diag(uint8_t num, char* key_word1, char* key_word2);

#endif /* LIS3DH_DIAG_H  */
