#ifndef GD5F1GQ5_DIAG_H
#define GD5F1GQ5_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "gd5f1gq5_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_GD5F1GQ5
#error "+HAS_GD5F1GQ5"
#endif

#ifndef HAS_GD5F1GQ5_DIAG
#error "+HAS_GD5F1GQ5_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool gd5f1gq5_read_block(uint8_t num, uint32_t block_num);
bool Gd5f1gq5ParameterPageElectricalDiag(const Gd5f1gq5ParameterPage_t* const Page);
bool Gd5f1gq5ParameterPageCapacityDiag(const Gd5f1gq5ParameterPage_t* const Page);
bool Gd5f1gq5ParameterPageVendorDiag(const Gd5f1gq5ParameterPage_t* const Page) ;
bool Gd5f1gq5ParameterPageMemoryOrganizationDiag(const Gd5f1gq5ParameterPage_t* const Page);
bool Gd5f1gq5ParameterPageDiag(const Gd5f1gq5ParameterPage_t* const Page);
bool gd5f1gq5_diag(void);
bool gd5f1gq5_diag_one(uint8_t num);
bool gd5f1gq5_get_features_diag(uint8_t num);

const char* Gd5f1gq5PhyAddrToStr(const Gd5f1gq5PhyAddress_t * const Node) ;
const char* Gd5f1gq5PhyAddressToStr(const uint32_t phy_address);
const char* Gd5f1gq5CommandToStr(const Gd5f1gq5Command_t cmmand);
const char* Gd5f1gq5ParameterPageToStr(const Gd5f1gq5ParameterPage_t * const Node);
const char* Gd5f1gq5ConfigToStr(const Gd5f1gq5Config_t* const Config);
const char* Gd5f1gq5NodeToStr(const Gd5f1gq5Handle_t* const Node);
const char* Gd5f1gq5IdToStr(const Gd5f1gq5ID_t * const pID);
const char* Gd5f1gq5RowAddressToStr(const Gd5f1gq5RowAddress_t *const Node);

const char* Gd5f1gq5RegProtectionToStr(const void * const memory);
const char* Gd5f1gq5RegFeatureB0ToStr(const void * const memory);
const char* Gd5f1gq5RegStatusC0ToStr(const void * const memory);
const char* Gd5f1gq5RegDriverStrengthToStr(const void * const memory);
const char* Gd5f1gq5RegStatusF0ToStr(const void * const memory);

#ifdef __cplusplus
}
#endif

#endif /* GD5F1GQ5_DIAG_H  */
