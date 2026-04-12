#include "fat_fs.h"

#include <string.h>

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(FatFs, fat_fs)
COMPONENT_GET_CONFIG(FatFs, fat_fs)

bool FatFsRetToRes(FRESULT ret, const char* const prefix) {
    bool res = false;
    if(FR_OK == ret) {
        res = true;
        LOG_DEBUG(FAT_FS, "%s,Ok", prefix);
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "%sErr,Ret:%u=%s", prefix, ret, FatFsResToStr(ret));
#endif
    }
    return res;
}

bool fat_fs_open(const uint8_t num, const char* const path, const BYTE mode) {
    bool res = false;
    LOG_DEBUG(FAT_FS, "%u,OpenFile:[%s],Mode:0x%X", num, path, mode);
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        strcpy(Node->path, path);
        FRESULT ret = f_open((FIL*)&Node->file, (const TCHAR*)Node->path, mode);
        res = FatFsRetToRes(ret, "Open");
        if(res) {
            LOG_DEBUG(TEST, "File:0x%s", path);
        } else {
            LOG_ERROR(TEST, "OpenErr,File:%s", path);
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool FatFsIsValidConfig(const FatFsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(FAT_FS, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool fat_fs_init_custom(void) {
    bool res = false;
    LOG_INFO(FAT_FS, "Version:%s", FAT_FS_VERSION);
    return res;
}

_WEAK_FUN_
bool fat_fs_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(FAT_FS, "Proc %u", i);
    FatFsHandle_t* Node = FatFsGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool fat_fs_init_common(const FatFsConfig_t* const Config, FatFsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->num = Config->num;
            Node->disk_num = Config->disk_num;
            res = true;
        }
    }
    return res;
}

bool fat_fs_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(FAT_FS, "FAT_FS%u", num);
#if 0
    log_level_get_set(DISK,LOG_LEVEL_DEBUG);
    log_level_get_set(FAT_FS,LOG_LEVEL_DEBUG);
#endif
    const FatFsConfig_t* Config = FatFsGetConfig(num);
    if(Config) {
        res = FatFsIsValidConfig(Config);
        if(res) {
#ifdef HAS_FAT_FS_DIAG
            LOG_WARNING(FAT_FS, "%s", FatFsConfigToStr(Config));
#endif
            FatFsHandle_t* Node = FatFsGetNode(num);
            if(Node) {
                res = fat_fs_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
                char path[100] = "\\";
                res = fat_fs_mount(num, MOUNT_IMMEDIATELY, path);
            } else {
                LOG_ERROR(FAT_FS, "FAT_FS%u,NodeErr", num);
            }
        } else {
            LOG_ERROR(FAT_FS, "FAT_FS%u,ConfigErr", num);
        }
    } else {
        LOG_PARN(FAT_FS, "FAT_FS%u,ConfigErr:", num);
    }
#if 0
    log_level_get_set(DISK,LOG_LEVEL_INFO);
    log_level_get_set(FAT_FS,LOG_LEVEL_INFO);
#endif
    return res;
}

bool fat_fs_write_file(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size) {
    bool res = false;
    if(file_name) {
        if(array) {
            if(size) {
                res = fat_fs_open(num, file_name, FA_WRITE | FA_OPEN_ALWAYS | FA_READ | FA_CREATE_ALWAYS);
                if(res) {
                    res = fat_fs_write_bin(num, array, size);
                    res = fat_fs_close(num);
                }
            }
        }
    }
    return res;
}

bool fat_fs_save_array(uint8_t num, const char* const file_name, const uint8_t* const array, uint32_t size) {
    bool res = false;
    if(file_name) {
        if(array && size) {
            FIL File = {0};
            FRESULT ret = FR_INT_ERR;
            ret = f_open(&File, (const TCHAR*)file_name, FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
            if(FR_OK == ret) {
                LOG_DEBUG(FAT_FS, "Open[%s]Ok", file_name);
                DWORD file_size = f_size(&File);
                ret = f_lseek(&File, file_size);
                if(FR_OK == ret) {
                    LOG_DEBUG(FAT_FS, "MoveToEndOk[%s],size:%u", file_name, file_size);
                    res = true;
                } else {
                    res = false;
#ifdef HAS_FAT_FS_DIAG
                    LOG_ERROR(FAT_FS, "Move,To,End,Err[%s],size:%u,ret:%u=%s", file_name, file_size, ret,
                              FatFsResToStr(ret));
#endif
                }

                if(res) {
                    res = false;
                    UINT ByteWritten = 0;
                    ret = f_write(&File, array, (UINT)size, &ByteWritten);
                    if(FR_OK == ret) {
                        if(ByteWritten == size) {
                            res = true;
                        } else {
                            res = false;
                            LOG_ERROR(FAT_FS, "Write,Size,Err");
                        }
                    } else {
                        res = false;
#ifdef HAS_FAT_FS_DIAG
                        LOG_ERROR(FAT_FS, "Write,Err[%s],ret:%u=%s", file_name, ret, FatFsResToStr(ret));
#endif
                    }
                }

                ret = f_close(&File);
                res = FatFsRetToRes(ret, "Close") && res;
            } else {
#ifdef HAS_FAT_FS_DIAG
                LOG_ERROR(FAT_FS, "Open[%s]Err:%d=%s", file_name, ret, FatFsResToStr(ret));
#endif
            }
        }
    }
    return res;
}

bool fat_fs_unlink(const uint8_t num, const char* const path) {
    bool res = false;
    FRESULT ret = f_unlink((const TCHAR*)path);
    if(FR_OK == ret) {
        LOG_INFO(FAT_FS, "UnLinkOk");
        res = true;
    } else {
        LOG_ERROR(FAT_FS, "UnLinkErr %u %s %s", ret, FatFsResToStr(ret), path);
        res = false;
    }

    return res;
}

bool fat_fs_read(uint8_t num, uint8_t* const data, const uint32_t size) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        FRESULT ret = 0;
        UINT extracted_bytes = 0;
        ret = f_read((FIL*)&Node->file, data, size, &extracted_bytes);
        res = FatFsRetToRes(ret, "Read");
        if(res) {
            res = false;
            if(extracted_bytes == size) {
                res = true;
#ifdef HAS_ARRAY_DIAG
                LOG_DEBUG(FAT_FS, "Read:%u byte", extracted_bytes);
                // print_mem(data, (uint32_t)extracted_bytes, true, true, true, true);
#endif
            }
        }
    }

    return res;
}

bool fat_fs_read_file(uint8_t num, const char* const path, uint8_t* const data, uint32_t size, uint32_t* const len) {
    bool res;
    LOG_DEBUG(FAT_FS, "%u,ReadFile:[%s],ToSize:%u", num, path, size);
    res = fat_fs_open(num, path, FA_READ | FA_OPEN_EXISTING);
    if(res) {
        res = fat_fs_read(num, data, size);
        res = fat_fs_close(num) && res;
    }
    return res;
}

bool fat_fs_open_dirr(uint8_t num, const char* const dirr_name) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        FRESULT ret = f_opendir(&Node->Dir, (const TCHAR*)&Node->dirr_name);
        res = FatFsRetToRes(ret, "OpenDir");
    }
    return res;
}

/*
  file_name - name of file to write in
  in_text - text must be in RAM
 */
bool fat_fs_write_line(uint8_t num, const char* const file_name, char* const in_text) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        LOG_DEBUG(FAT_FS, "File:[%s],text:[%s]", file_name, in_text);
        static bool rec_prot = false;
        if(false == rec_prot) {
            rec_prot = true;
            uint32_t wr_len = 0;
            wr_len = strlen(in_text);
            strcat(in_text, CRLF);
            wr_len += 2;
            res = fat_fs_save_array(num, file_name, (const uint8_t* const)in_text, (uint32_t)wr_len);
            rec_prot = false;
        }
    }
    return res;
}

bool fat_fs_write_bin(uint8_t num, const uint8_t* const array, uint32_t size) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        FRESULT ret;
        UINT written = 0;
        ret = f_write((FIL*)&Node->file, (const void*)array, (UINT)size, (UINT*)&written);
        res = FatFsRetToRes(ret, "Write");
        if(res) {
            LOG_INFO(FAT_FS, "Writen:%u,byte,Ok", written);
            res = false;
            if(written == size) {
                res = true;
            }
        }
    }
    return res;
}

bool fat_fs_scan_light(uint8_t num, const char* const path) {
    bool res = false;

    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        // DIR dir = { 0 };
        FRESULT ret = FR_INT_ERR;
        ret = f_opendir(&Node->Dir, path);
        if(FR_OK == ret) {
            FILINFO fno = {0};
            for(;;) {
                ret = f_readdir(&Node->Dir, &fno); /* Read a directory item */
                if(FR_OK == ret) {
                    if(0 == fno.fname[0]) {
                        break;
                    }
                    if('.' == fno.fname[0]) {
                        continue;
                    } else {
                        if(0 == (fno.fattrib & AM_DIR)) {
                            cli_printf("%s/%s" CRLF, path, fno.fname);
                        }
                    }
                } else {
                    break;
                }
            }
        } else {
#ifdef HAS_FAT_FS_DIAG
            LOG_ERROR(FAT_FS, "OpenDirErr:%d=%s", ret, FatFsResToStr(ret));
#endif
            res = false;
        }
    }
    return res;
}

bool fat_fs_root(uint8_t num) {
    bool res = false;
    res = fat_fs_scan_light(num, "");
    return res;
}

bool fat_fs_cat(uint8_t num, const char* const file_name) {
    bool res = false;
    LOG_INFO(FAT_FS, "Cat:[%s]", file_name);
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {

        FRESULT ret;
        ret = f_open(&Node->file, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
        if(FR_OK == ret) {
            res = true;
            LOG_DEBUG(FAT_FS, "OpenOk [%s]", file_name);
            while(1) {
                char RxBuff[2] = {0};
                uint32_t read_cnt = 0;
                ret = f_read(&Node->file, RxBuff, 1, (UINT*)&read_cnt);
                if(FR_OK == ret) {
                    if(1 == read_cnt) {
                        cli_printf("%c", RxBuff[0]);
                    } else {
                        break;
                    }
                }
            }
            ret = f_close(&Node->file);
            res = FatFsRetToRes(ret, "Close");
        } else {
#ifdef HAS_FAT_FS_DIAG
            LOG_ERROR(FAT_FS, "Open[%s]Err %u=%s", file_name, ret, FatFsResToStr(ret));
#endif
        }
    }
    return res;
}

bool fat_fs_read_dirr(uint8_t num) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        FRESULT ret = f_readdir(&Node->Dir, &Node->FileInfo);
        res = FatFsRetToRes(ret, "ReadDor");
        if(res) {
            FatFsParseFileInfo(&Node->FileInfo);
        }
    }
    return res;
}

bool fat_fs_mount(uint8_t num, uint8_t opt, char* path) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        // char path[100] = "\\";
        LOG_INFO(FAT_FS, "Mount Path [%s] Opt:%u", path, opt);
        FRESULT ret;
        ret = f_mount((FATFS*)&Node->fileSystem, (const TCHAR*)path, (BYTE)opt);
        res = FatFsRetToRes(ret, "Mount");
        if(FR_NO_FILESYSTEM == ret) {
            res = fat_fs_format(num, FM_FAT32, 512);
        }
    }
    return res;
}

bool fat_fs_format(uint8_t num, BYTE format_opt, DWORD allocation_unit) {
    bool res = false;
    // BYTE format_opt = FM_FAT;
    // DWORD allocation_unit = 512;

    BYTE WorkingBuffer[_MAX_SS] = {0};
    LOG_INFO(FAT_FS, "Call f_mkfs Opt:%s, AllocUnit:%u byte...", FatFormatOptionsToStr(format_opt), allocation_unit);
    FRESULT ret = FR_DISK_ERR;
    ret = f_mkfs("",                   /* [IN] Logical drive number */
                 format_opt,           /* [IN] Format options (FM_FAT) */
                 allocation_unit,      /* [IN]Size of allocation unit (cluster) [byte] */
                 WorkingBuffer,        /* [-] Pointer to working buffer */
                 sizeof(WorkingBuffer) /* [IN] Size of working buffer */
    );

    res = FatFsRetToRes(ret, "MakeFS");

    return res;
}

bool fat_fs_close(uint8_t num) {
    bool res = false;
    FatFsHandle_t* Node = FatFsGetNode(num);
    if(Node) {
        FRESULT ret;
        ret = f_close((FIL*)&Node->file);
        res = FatFsRetToRes(ret, "Close");
    } else {
        LOG_ERROR(FAT_FS, "Usage ftfsc path");
    }
    return res;
}

COMPONENT_INIT_PATTERT(FAT_FS, FAT_FS, fat_fs)
COMPONENT_PROC_PATTERT(FAT_FS, FAT_FS, fat_fs)
