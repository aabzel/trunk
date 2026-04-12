#ifndef STORE_FS_DIAG_H
#define STORE_FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "store_fs_types.h"
#include "storage_file_ids.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_STORE_FS
#error "+HAS_STORE_FS"
#endif /*HAS_STORE_FS*/

#ifndef HAS_STORE_FS_DIAG
#error "+HAS_STORE_FS_DIAG"
#endif /*HAS_DIAG_STORE_FS*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool store_fs_diag(uint8_t num, char* keyWord1, char* keyWord2) ;
const char* StorageToStr(const StorageId_t id);
const char* StoreFsDataToStr(const StorageId_t id, const void* const data);
const char* StoreFsConfigToStr(const StoreFsConfig_t* const Config);
const char* StoreFsNodeToStr(const StoreFsHandle_t* const Node);
const char* store_fs_val2str(StorageId_t id, uint8_t* const value, uint32_t size) ;

#ifdef __cplusplus
}
#endif

#endif /* STORE_FS_DIAG_H  */
