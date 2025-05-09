#include "file_api.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"
#include "macro_utils.h"
#ifdef HAS_STRING
//#include "str_utils_ex.h"
#endif

#ifdef HAS_FAT_FS
#include "fat_fs_drv.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

#if defined(HAS_FAT_FS) && defined(HAS_FILE_PC)
#error "config error"
#endif

int32_t file_line_cnt(const char* const file_name) {
    int32_t line_cnt = -1;
#ifdef HAS_FAT_FS
    line_cnt = fat_fs_file_line_cnt(file_name);
#endif

#ifdef HAS_FILE_PC
    line_cnt = file_pc_line_cnt(file_name);
#endif
    LOG_DEBUG(FILE_API, "line:%u,File:[%s]",line_cnt,file_name);
    if(line_cnt < 0) {
        LOG_ERROR(FILE_API, "LineCntErr");
    }
    return line_cnt;
}

int32_t file_get_size(const char* const file_name) {
    int32_t fize_size = 0;

#ifdef HAS_FAT_FS
    fize_size = fat_fs_file_get_size(file_name);
#endif

#ifdef HAS_FILE_PC
    fize_size = file_pc_get_size(file_name);
#endif

    return fize_size;
}

/*
 * data address to put result
 * size - bures to read
 * read_size - real read size
 * */
bool file_load_to_array(const char* const file_name, uint8_t* const data, uint32_t size, uint32_t* const read_size) {
    bool res = false;
#ifdef HAS_FAT_FS
    res = fat_fs_load_to_array(file_name, data, size, read_size);
#endif

#ifdef HAS_FILE_PC
    res = file_pc_load_to_array(file_name, data, size, read_size);
#endif
    return res;
}

/*save to the end of file*/
bool file_save_array(const char* const file_name, const uint8_t* const data, size_t size) {
    bool res = false;

#ifdef HAS_FAT_FS
    res = fat_fs_save_array(file_name, data, size);
#endif

#ifdef HAS_FILE_PC
    res = file_pc_save_array(file_name, data, size);
#endif
    return res;
}

bool file_array_to_binary_file(const char* const file_name, const uint8_t* const data, size_t size) {
    bool res = false;
#ifdef HAS_FAT_FS
    res = fat_fs_save_array(file_name, data, size);
#endif

#ifdef HAS_FILE_PC
    res = file_pc_array_to_binary_file(file_name, data, size);
#endif
    return res;
}

bool file_api_open_re(FileApiHandle_t* const Node, const char* const file_name) {
    bool res = false;
    if(Node) {
#ifdef HAS_FAT_FS
        FRESULT ret = FR_INT_ERR;
        ret = f_open(&Node->FatFsFile, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
        res = FatFsRet2Res(ret, "Open");
#endif

#ifdef HAS_FILE_PC
        Node->FilePtr = fopen(file_name, "r");
        if(Node->FilePtr) {
            res = true;
        }
#endif
        if(false == res) {
            LOG_ERROR(FILE_API, "Open[%s]Err", file_name);
        }
    }
    return res;
}

bool file_api_close(FileApiHandle_t* const Node) {
    bool res = false;
    if(Node) {
#ifdef HAS_FAT_FS
        FRESULT ret = FR_INT_ERR;
        ret = f_close(&Node->FatFsFile);
        res = FatFsRet2Res(ret, "Close");
#endif

#ifdef HAS_FILE_PC
        int ret = fclose(Node->FilePtr);
        if(0 == ret) {
            res = true;
        }
#endif
    }
    return res;
}

bool file_api_gets(FileApiHandle_t* const Node, char* const line, size_t size, size_t* const read_len_prt) {
    bool res = false;
    if(Node) {
        if(line) {
            if(size) {
                if(read_len_prt) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
#ifdef HAS_FAT_FS
        res = fat_fs_read_line(&Node->FatFsFile, line, size, read_len_prt);
#endif

#ifdef HAS_FILE_PC
        // http://all-ht.ru/inf/prog/c/func/fgets.html
        if(Node->FilePtr) {
            char* estr = fgets(line, (int)size, Node->FilePtr);
            if(estr) {
                *read_len_prt = strlen(line);
                res = true;
            } else {
                res = false;
            }
        } else {
            LOG_ERROR(FILE_API, "NotOpened");
            res = false;
        }
#endif
    }
    return res;
}
