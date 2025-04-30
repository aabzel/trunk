#ifndef FAT_FS_DRV_H
#define FAT_FS_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef HAS_FAT_FS
#error "+HAS_FAT_FS"
#endif

#include "ff.h"

#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif

bool FatFsRet2Res(FRESULT ret, const char* const prefix);
bool fat_fs_cat(char* file_name);
bool fat_fs_init(void);
bool fat_fs_load_to_array(const char* const file_name, uint8_t* const data, uint32_t size, uint32_t* const read_size) ;
bool fat_fs_root(void);
bool fat_fs_scan_light(const char* const path  );
bool fat_fs_save_array(const char* const file_name, const uint8_t* const array, size_t size);
bool fat_fs_save_double(const char* const file_name, double value);
bool fat_fs_write(const char* const file_name, char* const text);
//bool ReadLine(char* const out_line, uint32_t size, uint32_t* const line_len);
bool fat_fs_read_line(FIL* FileNode, char* const out_line, size_t size, size_t* const line_len);
int32_t fat_fs_file_line_cnt(const char* const file_name);
int32_t fat_fs_file_get_size(const char* const file_name);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FAT_FS_DRV_H*/
