#ifndef STARAGE_H
#define STARAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "storage_types.h"
#include "storage_config.h"

#ifdef HAS_STORAGE_DIAG
#include "storage_diag.h"
#endif
bool storage_proc_cmd(uint8_t tbfp_num, const uint8_t* const payload, const uint32_t size);
bool StorageIsValidParam(const StorageItem_t* const Config);
uint32_t storage_get_type_len(const StorageType_t type);
uint32_t storage_get_len(const StorageId_t storage_id);
StorageType_t storage_get_type(const StorageId_t id);
StorageType_t storage_get_id_type(  StorageId_t id);
StorageItem_t* StorageGetNode(const StorageId_t id);
StoragePhysicalQuantity_t storage_units_to_physical_quantity(const StorageUnits_t units);





#ifdef __cplusplus
}
#endif

#endif /* STARAGE_H */
