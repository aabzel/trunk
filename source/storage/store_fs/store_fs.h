#ifndef STORE_FS_MCAL_H
#define STORE_FS_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "store_fs_config.h"
#include "store_fs_types.h"
#include "storage_file_ids.h"

#ifdef HAS_STORE_FS_DIAG
#include "store_fs_diag.h"
#endif

/* API */
const StoreFsConfig_t* StoreFsGetConfig(uint8_t num);
StoreFsHandle_t* StoreFsGetNode(uint8_t num);
bool StoreFsIsValidConfig(const StoreFsConfig_t* const Config);

#ifdef HAS_STORE_FS_CUSTOM
const StoreFsInfo_t* StoreFsGetInfo(uint8_t num);
#endif

bool store_fs_mcal_init(void);
bool store_fs_init_custom(void);
bool store_fs_init_one(uint8_t num);
bool store_fs_init_common(const StoreFsConfig_t* const Config,
                          StoreFsHandle_t* const Node);

bool store_fs_proc_one(uint8_t num);
bool store_fs_proc(void);

/*setters*/
bool store_fs_invalidate(const uint8_t num, const StorageId_t id);
bool store_fs_set(uint8_t num, StorageId_t id, const void* const data);
bool store_fs_set_verify(uint8_t num, StorageId_t id, const void* const data);
bool store_fs_set_lazy(uint8_t num, StorageId_t id, const void* const data);


/*getters*/
bool store_fs_get(uint8_t num, StorageId_t id, void* const out_data);
bool store_fs_load(uint8_t num, StorageId_t id, void* const out_data);

#ifdef __cplusplus
}
#endif

#endif /* STORE_FS_MCAL_H */
