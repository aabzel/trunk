#ifndef FAT_FS_DIAG_H
#define FAT_FS_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "fat_fs_types.h"
#include "ff.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

#ifndef HAS_FAT_FS_DIAG
#error "+HAS_FAT_FS_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

const char* FatFsFileAttrToStr(BYTE fattrib);
const char* FatFormatOptionsToStr(BYTE format_opt);
const char* FatFsResToStr(FRESULT code);
const char* FatFsFileToStr(const FIL*const  file);
const char* FatFsConfigToStr(const FatFsConfig_t* const Config);
const char* FatFsNodeToStr(const FatFsHandle_t* const Node);
bool fat_fs_scan(const char* const path);
bool FatFsParseFileInfo(FILINFO* FileInfo);
bool fat_fs_diag(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* FAT_FS_DIAG_H  */
