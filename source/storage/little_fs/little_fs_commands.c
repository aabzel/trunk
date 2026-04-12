#include "little_fs_commands.h"

#include "array_diag.h"
#include "convert.h"
#include "little_fs.h"
#include "log.h"

bool little_fs_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        uint8_t data[200] = {0};
        uint32_t len = 0;
        res = little_fs_read(num, path, data, sizeof(data), &len);
        log_info_res(LITTLE_FS, res, "Read");
        if(res) {
            print_hex(data, len);
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrl Num FileName");
    }

    return res;
}

bool little_fs_read_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(res) {
        uint8_t data[200] = {0};
        uint32_t len = 0;
        res = little_fs_read_ll(num, data, sizeof(data), &len);
        log_info_res(LITTLE_FS, res, "Read");
        if(res) {
            print_hex(data, len);
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrl Num");
    }

    return res;
}

bool little_fs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    uint8_t data[100] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    char path[300] = {0};
    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], data, sizeof(data), &size);
        log_info_res(LITTLE_FS, res, "Data");
        if(!res) {
            strcpy((char*)data, argv[2]);
            size = strlen(argv[2]);
            res = true;
        }
    }

    if(res) {
        res = little_fs_write(num, path, data, size);
        log_info_res(LITTLE_FS, res, "Write");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfw Num Path Data");
    }
    return res;
}

bool little_fs_write_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    uint8_t data[100] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LITTLE_FS, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        log_info_res(LITTLE_FS, res, "Data");
        if(!res) {
            strcpy((char*)data, argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = little_fs_write_ll(num, data, size);
        log_info_res(LITTLE_FS, res, "Write");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfw Num Data");
    }
    return res;
}

bool little_fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = little_fs_diag(1);
        log_info_res(LITTLE_FS, res, "Diag");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage: fdat");
    }

    return res;
}

bool little_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = little_fs_mcal_init();
        log_info_res(LITTLE_FS, res, "Init");
    }
    return res;
}

bool little_fs_open_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t mode = LFS_O_RDWR | LFS_O_CREAT;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    char path[300] = {0};
    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(3 <= argc) {
        res = try_str2int32(argv[2], &mode);
    }

    if(res) {
        res = little_fs_open(num, path, mode);
        log_info_res(LITTLE_FS, res, "Open");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfo path mode");
    }
    return res;
}

bool little_fs_remove_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        res = little_fs_remove(num, path);
        log_info_res(LITTLE_FS, res, "ReMove");
    } else {
        LOG_ERROR(LITTLE_FS, "Usage lfrm path");
    }
    return res;
}

#if 0

#include "little_fs_commands.h"

#include <string.h>

#include "array_diag.h"
#include "debug_info.h"
#include "ff.h"
#include "integer.h"
#include "little_fs_config.h"
#include "little_fs_diag.h"
#include "little_fs_drv.h"
#include "log.h"
#include "log_utils.h"


bool little_fs_mount_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[100] = "\\";
    BYTE opt = 1;
    FRESULT ret;
    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], (uint8_t*)&opt);
    }

    if(res) {
#ifdef HAS_SD_CARD
        log_level_t orig_ll = log_level_get_set(SD_CARD, LOG_LEVEL_DEBUG);
#endif

        LOG_INFO(LITTLE_FS, "Mount Path [%s] Opt:%u", path, opt);
        ret = f_mount((FATFS*)&FatFsInstance.fileSystem, (const TCHAR*)path, (BYTE)opt);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "MountOk");
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "MountErr", ret, FatFsResToStr(ret));
            res = false;
        }
#ifdef HAS_SD_CARD
        set_log_level(SD_CARD, orig_ll);
#endif
    }
    return res;
}


bool little_fs_read_dirr_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
        FRESULT ret = f_readdir(&FatFsInstance.Dir, &FatFsInstance.FileInfo);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "ReadDirOk");
            FatFsParseFileInfo(&FatFsInstance.FileInfo);
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "ReadDirErr %u %s", ret, FatFsResToStr(ret));
            res = false;
        }
    }
    return res;
}

bool little_fs_file_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    char filename[100] = "";
    memset(text, 0, sizeof(text));
    uint32_t len = 0;
    if(1 <= argc) {
        strcpy(filename, argv[0]);
        res = true;
    }
    if(2 <= argc) {
        strcpy(text, argv[1]);
        len = strlen(argv[1]);
        res = true;
    }
    if(res) {
        LOG_INFO(LITTLE_FS, "File[%s] text[%s] Len:%u", filename, text, len);
        res = little_fs_write(filename, text);
        if(res) {
            LOG_INFO(LITTLE_FS, "WrireOk");
        } else {
            LOG_ERROR(LITTLE_FS, "WrireErr");
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage ffw file text");
    }
    return res;
}

bool little_fs_open_dirr_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        strcpy(FatFsInstance.dirr_name, "/");
    }
    if(1 <= argc) {
        strcpy(FatFsInstance.dirr_name, argv[0]);
        res = true;
    }
    if(res) {
        FRESULT ret = f_opendir(&FatFsInstance.Dir, (const TCHAR*)FatFsInstance.dirr_name);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "OpenDirOk");
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "OpenDirErr %u %s %s", ret, FatFsResToStr(ret), FatFsInstance.dirr_name);
            res = false;
        }
    }
    return res;
}

bool little_fs_unlink_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }
    if(res) {
        FRESULT ret = f_unlink((const TCHAR*)FatFsInstance.path);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "UnLinkOk");
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "UnLinkErr %u %s %s", ret, FatFsResToStr(ret), FatFsInstance.path);
            res = false;
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage funl path");
    }
    return res;
}


bool little_fs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    UINT bw = 0;
    FRESULT ret;
    uint32_t array_len = 0;
    uint8_t array[500];
    if(1 <= argc) {
        res = try_str2array(argv[0], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_ERROR(LITTLE_FS, "ParseErr array %s", argv[0]);
            strcpy((char*)array, argv[0]);
            res = true;
        }
    }

    if(res) {
        ret = f_write((FIL*)&FatFsInstance.file, (const void*)array, (UINT)array_len, (UINT*)&bw);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "Write %u byte Ok", bw);
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "WriteErr %u %s", ret, FatFsResToStr(ret));
            res = false;
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage ftfsw text");
    }
    return res;
}

bool little_fs_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    FRESULT ret = 0;
    uint8_t RxData[500] = {0};
    UINT extracted_bytes = 0;
    UINT btr = 1;
    if(0 <= argc) {
        res = false;
    }
    if(1 <= argc) {
        res = try_str2uint32(argv[0], (uint32_t*)&btr);
    }
    if(res) {
        ret = f_read((FIL*)&FatFsInstance.file, RxData, btr, &extracted_bytes);
        if(FR_OK == ret) {
#ifdef HAS_ARRAY_DIAG
            LOG_INFO(LITTLE_FS, "Read %u byte Ok", extracted_bytes);
            print_mem(RxData, (uint32_t)extracted_bytes, true, true, true, true);
            res = true;
#endif
        } else {
            LOG_ERROR(LITTLE_FS, "ReadErr %u %s", ret, FatFsResToStr(ret));
            res = false;
        }
    }
    return res;
}

bool little_fs_cat_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }

    if(res) {
        res = little_fs_cat(FatFsInstance.path);
        if(res) {
            LOG_INFO(LITTLE_FS, "CatOk");
        } else {
            LOG_ERROR(LITTLE_FS, "CatErr");
        }
    }
    return res;
}

bool little_fs_close_command(int32_t argc, char* argv[]) {
    bool res = false;
    FRESULT ret;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }
    if(res) {
        LOG_INFO(LITTLE_FS, "CloseFile:[%s]", FatFsInstance.path);
        ret = f_close((FIL*)&FatFsInstance.file);
        if(FR_OK == ret) {
            LOG_INFO(LITTLE_FS, "CloseOk");
            res = true;
        } else {
            LOG_ERROR(LITTLE_FS, "CloseErr %u %s", ret, FatFsResToStr(ret));
            res = false;
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage ftfsc path");
    }
    return res;
}

bool little_fs_seek_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool little_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = little_fs_init();
    return res;
}

/*
 * fatff 0 4096
//
 * FAT16 fatff 1 512
// FAT32 fatff 2 512
//
//EXFAT fatff 4 512
//ANY fatff 7 512
//fatff 0 1024
*/
bool little_fs_format_command(int32_t argc, char* argv[]) {
    bool res = false;
    FRESULT ret = FR_DISK_ERR;
    BYTE format_opt = FM_FAT;
    DWORD allocation_unit = 512;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &format_opt);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &allocation_unit);
    }

    if(res) {
        BYTE WorkingBuffer[_MAX_SS];
        log_level_t orig_ll = LOG_LEVEL_UNKNOWN;
#ifdef HAS_SD_CARD
        orig_ll = log_level_get_set(SD_CARD, LOG_LEVEL_INFO);
#endif

#ifdef HAS_SDIO
        orig_ll = log_level_get_set(LG_SDIO, LOG_LEVEL_INFO);
#endif
        LOG_INFO(LITTLE_FS, "Call f_mkfs Opt:%s, AllocUnit:%u byte...", FatFormatOptionsToStr(format_opt), allocation_unit);
        ret = f_mkfs("",                   /* [IN] Logical drive number */
                     format_opt,           /* [IN] Format options (FM_FAT) */
                     allocation_unit,      /* [IN]Size of allocation unit (cluster) [byte] */
                     WorkingBuffer,        /* [-] Pointer to working buffer */
                     sizeof(WorkingBuffer) /* [IN] Size of working buffer */
        );
#ifdef HAS_SD_CARD
        set_log_level(SD_CARD, orig_ll);
#endif

#ifdef HAS_SDIO
        set_log_level(LG_SDIO, orig_ll);
#endif

        if(FR_OK == ret) {
            res = true;
            LOG_INFO(LITTLE_FS, "MakeFsOk");
        } else {
            LOG_ERROR(LITTLE_FS, "MakeFsErr %u %s", ret, FatFsResToStr(ret));
        }
    } else {
        LOG_ERROR(LITTLE_FS, "Usage fatff FormatOpt AllocationUnit");
    }
    return res;
}

bool little_fs_root_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = little_fs_root();
    return res;
}

bool little_fs_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[20] = "";
    if(0 <= argc) {
        strcpy(path, "");
        res = true;
    }

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = little_fs_scan(path);
    } else {
        LOG_ERROR(LITTLE_FS, "Usage ffs path");
    }
    return res;
}

#endif

bool little_fs_file_info_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[20] = "\\"; //
    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    LittleFsHandle_t* Node = LittleFsGetNode(1);
    if(Node) {
        struct lfs_info info = {0};
        int ret = lfs_stat(&Node->lfs, path, &info);
        res = LittleFsRetToRes(ret);
    }
    return res;
}

/*
little_fs_ls ..
little_fs_ls .
 * */
bool little_fs_list_command(int32_t argc, char* argv[]) {
    bool res = false;
    char path[40] = "\\"; //    .      backslash

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        strcpy(path, argv[0]);
        res = true;
    }

    if(res) {
        res = little_fs_list(1, path);
        log_info_res(LITTLE_FS, res, "List");
    }
    return res;
}
