#ifndef LITTLE_FS_CONFIG_H
#define LITTLE_FS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "little_fs_types.h"
#include "little_fs_dep.h"


#define LITTLE_FS_FLASH_SIZE MBYTE_BYTE(1)
#define LITTLE_FS_NOR_FLASH_NUM 1
#define LITTLE_FS_BLOCK_SIZE  (4096)
#define LITTLE_FS_PAGE_SIZE  256

#define LITTLE_FS_CACHE_SIZE (LITTLE_FS_PAGE_SIZE)

extern const LittleFsConfig_t LittleFsConfig[];
extern LittleFsHandle_t LittleFsInstance[];

uint32_t little_fs_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* LITTLE_FS_CONFIG_H */
