#include "fat_fs_commands.h"

#include <string.h>

#include "array_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "fat_fs_config.h"
#include "fat_fs_diag.h"
#include "fat_fs_drv.h"
#include "ff.h"
#include "integer.h"
#include "log.h"
#include "log_utils.h"

bool fat_fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool fat_fs_mount_command(int32_t argc, char* argv[]) {
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

        LOG_INFO(FAT_FS, "Mount Path [%s] Opt:%u", path, opt);
        ret = f_mount((FATFS*)&FatFsInstance.fileSystem, (const TCHAR*)path, (BYTE)opt);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "MountOk");
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "MountErr", ret, FatFsRes2Str(ret));
            res = false;
        }
#ifdef HAS_SD_CARD
        set_log_level(SD_CARD, orig_ll);
#endif
    }
    return res;
}

bool fat_fs_read_dirr_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
        FRESULT ret = f_readdir(&FatFsInstance.Dir, &FatFsInstance.FileInfo);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "ReadDirOk");
            FatFsParseFileInfo(&FatFsInstance.FileInfo);
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "ReadDirErr %u %s", ret, FatFsRes2Str(ret));
            res = false;
        }
    }
    return res;
}

bool fat_fs_file_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    char filename[100] = "";
    char text[100] = "";
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
        LOG_INFO(FAT_FS, "File[%s] text[%s] Len:%u", filename, text, len);
        res = fat_fs_write(filename, text);
        if(res) {
            LOG_INFO(FAT_FS, "WrireOk");
        } else {
            LOG_ERROR(FAT_FS, "WrireErr");
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage ffw file text");
    }
    return res;
}

bool fat_fs_open_dirr_command(int32_t argc, char* argv[]) {
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
            LOG_INFO(FAT_FS, "OpenDirOk");
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "OpenDirErr %u %s %s", ret, FatFsRes2Str(ret), FatFsInstance.dirr_name);
            res = false;
        }
    }
    return res;
}

bool fat_fs_unlink_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }
    if(res) {
        FRESULT ret = f_unlink((const TCHAR*)FatFsInstance.path);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "UnLinkOk");
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "UnLinkErr %u %s %s", ret, FatFsRes2Str(ret), FatFsInstance.path);
            res = false;
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage funl path");
    }
    return res;
}

bool fat_fs_open_command(int32_t argc, char* argv[]) {
    bool res = false;
    BYTE mode = FA_READ | FA_OPEN_EXISTING;

    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mode);
    }

    if(res) {
        LOG_INFO(FAT_FS, "Open File:[%s]", FatFsInstance.path);
        FRESULT ret = f_open((FIL*)&FatFsInstance.file, (const TCHAR*)FatFsInstance.path, mode);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "OpenOk");
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "OpenErr %u=%s %s", ret, FatFsRes2Str(ret), FatFsInstance.path);
            res = false;
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfso path mode");
    }

    return res;
}

bool fat_fs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    UINT bw = 0;
    FRESULT ret;
    size_t array_len = 0;
    uint8_t array[500];
    if(1 <= argc) {
        res = try_str2array(argv[0], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_ERROR(FAT_FS, "ParseErr array %s", argv[0]);
            strcpy((char*)array, argv[0]);
            res = true;
        }
    }

    if(res) {
        ret = f_write((FIL*)&FatFsInstance.file, (const void*)array, (UINT)array_len, (UINT*)&bw);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "Write %u byte Ok", bw);
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "WriteErr %u %s", ret, FatFsRes2Str(ret));
            res = false;
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfsw text");
    }
    return res;
}

bool fat_fs_read_command(int32_t argc, char* argv[]) {
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
            LOG_INFO(FAT_FS, "Read %u byte Ok", extracted_bytes);
            print_mem(RxData, (uint32_t)extracted_bytes, true, true, true, true);
            res = true;
#endif
        } else {
            LOG_ERROR(FAT_FS, "ReadErr %u %s", ret, FatFsRes2Str(ret));
            res = false;
        }
    }
    return res;
}

bool fat_fs_cat_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }

    if(res) {
        res = fat_fs_cat(FatFsInstance.path);
        if(res) {
            LOG_INFO(FAT_FS, "CatOk");
        } else {
            LOG_ERROR(FAT_FS, "CatErr");
        }
    }
    return res;
}

bool fat_fs_close_command(int32_t argc, char* argv[]) {
    bool res = false;
    FRESULT ret;
    if(1 <= argc) {
        strcpy(FatFsInstance.path, argv[0]);
        res = true;
    }
    if(res) {
        LOG_INFO(FAT_FS, "CloseFile:[%s]", FatFsInstance.path);
        ret = f_close((FIL*)&FatFsInstance.file);
        if(FR_OK == ret) {
            LOG_INFO(FAT_FS, "CloseOk");
            res = true;
        } else {
            LOG_ERROR(FAT_FS, "CloseErr %u %s", ret, FatFsRes2Str(ret));
            res = false;
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfsc path");
    }
    return res;
}

bool fat_fs_seek_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool fat_fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = fat_fs_init();
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
bool fat_fs_format_command(int32_t argc, char* argv[]) {
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
        LOG_INFO(FAT_FS, "Call f_mkfs Opt:%s, AllocUnit:%u byte...", FatFormatOptions2Str(format_opt), allocation_unit);
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
            LOG_INFO(FAT_FS, "MakeFsOk");
        } else {
            LOG_ERROR(FAT_FS, "MakeFsErr %u %s", ret, FatFsRes2Str(ret));
        }
    } else {
        LOG_ERROR(FAT_FS, "Usage fatff FormatOpt AllocationUnit");
    }
    return res;
}

bool fat_fs_root_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = fat_fs_root();
    return res;
}

bool fat_fs_scan_command(int32_t argc, char* argv[]) {
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
        res = fat_fs_scan(path);
    } else {
        LOG_ERROR(FAT_FS, "Usage ffs path");
    }
    return res;
}
