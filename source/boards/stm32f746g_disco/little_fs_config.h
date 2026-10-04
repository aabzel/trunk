#ifndef LITTLE_FS_CONFIG_H
#define LITTLE_FS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "little_fs_types.h"
#include "little_fs_dep.h"

#define LITTLE_FS_NOR_FLASH_NUM 1
#define GD5F1GQ5_TOTAL_BLOCKS 1000


//#define LITTLE_FS_CACHE_SIZE (GD5F1GQ5_PAGE_SIZE*2)
#define LITTLE_FS_CACHE_SIZE (GD5F1GQ5_PAGE_SIZE)
#define LITTLE_FS_LOOKAHEAD_SIZE (GD5F1GQ5_PAGE_SIZE)

extern const LittleFsConfig_t LittleFsConfig[];
extern LittleFsHandle_t LittleFsInstance[];

uint32_t little_fs_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* LITTLE_FS_CONFIG_H */
