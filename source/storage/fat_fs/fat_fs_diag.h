#ifndef FAT_FS_DIAG_H
#define FAT_FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

#ifndef HAS_FAT_FS_DIAG
#error "+HAS_FAT_FS_DIAG"
#endif

#include "ff.h"

const char* FatFsFileAttr2Str(BYTE fattrib);
bool fat_fs_scan(const char* const path  );
const char* FatFormatOptions2Str(BYTE format_opt);
const char* DiskCmd2Str(uint8_t cmd);
bool FatFsParseFileInfo(FILINFO* FileInfo);
const char* FatFsRes2Str(FRESULT code);
const char* DiskIoCtlCmd2Str(uint8_t const ioctl_code);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FAT_FS_DIAG_H*/
