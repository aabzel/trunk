#ifndef FAT_FS_TYPES_H
#define FAT_FS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "fat_fs_const.h"
#include "ff.h"

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

typedef struct {
    char path[100];
    char dirr_name[100];
    FIL file;
    FATFS fileSystem;
    FILINFO FileInfo;
    DIR Dir;
} FatFs_t;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FAT_FS_TYPES_H*/
