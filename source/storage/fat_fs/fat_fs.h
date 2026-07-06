#ifndef FAT_FS_MCAL_H
#define FAT_FS_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "fat_fs_config.h"
#include "fat_fs_types.h"
#include "ff.h"
#include "fat_fs.h"

#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif


/* API */
const FatFsConfig_t* FatFsGetConfig(uint8_t num);
FatFsHandle_t* FatFsGetNode(uint8_t num);

bool FatFsIsValidConfig(const FatFsConfig_t* const Config);

#ifdef HAS_FAT_FS_CUSTOM
const FatFsInfo_t* FatFsGetInfo(uint8_t num);
#endif

bool fat_fs_mcal_init(void);
bool fat_fs_init_custom(void);
bool fat_fs_init_one(uint8_t num);
bool fat_fs_init_common(const FatFsConfig_t* const Config,
                              FatFsHandle_t* const Node);

bool fat_fs_proc_one(uint8_t num);
bool fat_fs_proc(void);

/*setters*/
bool fat_fs_format(uint8_t num, BYTE format_opt,DWORD allocation_unit  ) ;
bool fat_fs_mount(uint8_t num,uint8_t opt,   char* path ) ;
bool fat_fs_save_array(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size) ;
bool fat_fs_save_array_puts(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size) ;
bool fat_fs_save_array_printf(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size);
bool fat_fs_write_line(uint8_t num, const char* const file_name, char* const in_text);
bool fat_fs_write_file(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size);

bool fat_fs_write_bin(uint8_t num, uint8_t const * const array, uint32_t size);
bool fat_fs_open_dirr(uint8_t num, const char* const dirr_name);
bool fat_fs_unlink(const uint8_t num, const char* const path);
bool fat_fs_open(const uint8_t num, const char* const path, const BYTE mode);
bool fat_fs_close(uint8_t num);

/*getters*/
int32_t fat_fs_file_line_cnt(const char* const path);
int32_t fat_fs_file_get_size(const char* const path);
bool fat_fs_scan_light(uint8_t num, const char* const path);
bool fat_fs_cat(uint8_t num, const char* const file_name) ;
bool fat_fs_read_dirr(uint8_t num) ;
bool FatFsRetToRes(FRESULT ret, const char* const prefix);
bool fat_fs_read(uint8_t num, uint8_t* const data, const uint32_t size) ;
bool fat_fs_read_file(uint8_t num, const char* const path, uint8_t* const data, uint32_t size, uint32_t* const len);

bool fat_fs_root(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* FAT_FS_MCAL_H */
