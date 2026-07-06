#ifndef FAT_FS_CONFIG_H
#define FAT_FS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "fat_fs_types.h"
#include "fat_fs_dep.h"

extern const FatFsConfig_t FatFsConfig[];
extern FatFsHandle_t FatFsInstance[];

uint32_t fat_fs_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* FAT_FS_CONFIG_H */
