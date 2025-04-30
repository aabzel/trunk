#ifndef FAT_FS_CONFIG_H
#define FAT_FS_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "fat_fs_types.h"

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

extern FatFs_t FatFsInstance;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FAT_FS_CONFIG_H*/
