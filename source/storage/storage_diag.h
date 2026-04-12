#ifndef STORAGE_DIAG_H
#define STORAGE_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "storage_types.h"

const char* StoragePhysicalQuantityToStr(const StoragePhysicalQuantity_t phy_qntity);
const char* StorageScaleToStr(const StorageScale_t scale);
const char* StorageIdToStr(const StorageId_t id);
const char* StorageItemToStr(const StorageItem_t* const Item );
const char* StorageFrameHeaderToStr(const StorageFrameHeader_t* const Header );
const char* StorageAccessToStr(const StorageAccess_t access);
const char* StorageTypeToStr(StorageType_t type);
const char* StorageUnitsToStr(const StorageUnits_t storage_uints);
const char* StorageDataToValueStr(const uint8_t* const buff, const uint32_t size, const StorageType_t type );
bool DataToValStrBuff(const  uint8_t* const buff, size_t value_len,
                      StorageType_t type, char* const  out_str, size_t str_size) ;

#ifdef __cplusplus
}
#endif

#endif /* STORAGE_DIAG_H */
