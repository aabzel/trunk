#include "fat_fs_drv.h"

#include <stdio.h>
#include <string.h>

#include "fat_fs_config.h"
#include "ff.h"
#include "log.h"
#include "log_utils.h"

// https://irtos.sourceforge.net/FAT32_ChaN/doc/en/lseek.html
// https://microsin.net/programming/file-systems/fatfs-file-system.html

bool fat_fs_init(void) {
    bool res = false;
    LOG_WARNING(FAT_FS, "init");
    FRESULT ret;
    set_log_level(FAT_FS, LOG_LEVEL_DEBUG);
#ifdef HAS_SDIO
    set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
#endif
#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
#endif
    set_log_level(DISK, LOG_LEVEL_DEBUG);
    LOG_INFO(FAT_FS, "Mount");
    ret = f_mount((FATFS*)&FatFsInstance.fileSystem, (const TCHAR*)"", (BYTE)MOUNT_IMMEDIATELY);
    if(FR_OK == ret) {
        LOG_INFO(FAT_FS, "MountOk");
        res = true;
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "MountErr %u=%s", ret, FatFsRes2Str(ret));
#endif
        res = false;
    }

    set_log_level(DISK, LOG_LEVEL_NOTICE);
    set_log_level(FAT_FS, LOG_LEVEL_NOTICE);
#ifdef HAS_SDIO
    set_log_level(LG_SDIO, LOG_LEVEL_INFO);
#endif
#ifdef HAS_SD_CARD
    set_log_level(SD_CARD, LOG_LEVEL_NOTICE);
#endif

    return res;
}

/*
 * data address to put result
 * size - bures to read
 * read_size - real read size
 * */
bool fat_fs_load_to_array(const char* const file_name, uint8_t* const data, uint32_t size, uint32_t* const read_size) {
    bool res = false;
    if(file_name) {
        if(data) {
            if(size) {

                if(read_size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;
    }

    return res;
}

bool fat_fs_read_line(FIL* FileNode, char* const out_line, size_t size, size_t* const line_len) {
    bool res = false;
    LOG_DEBUG(FAT_FS, "ReadLen,Size:%u Byte", size);
    if(FileNode) {
        size_t i = 0;
        //*line_len = 0;
        while(1) {
            char RxBuff[2] = {0};
            FRESULT ret = FR_INT_ERR;
            UINT read_cnt = 0;
            ret = f_read(FileNode, RxBuff, 1, (UINT*)&read_cnt);
            if(FR_OK == ret) {
                LOG_DEBUG(FAT_FS, "Read:[%u]=[%c],Rx:%u Byte", i, RxBuff[0], read_cnt);
                if(1 == read_cnt) {
                    if(('\r' == RxBuff[0]) || ('\n' == RxBuff[0])) {
                        out_line[i] = '\0';
                        res = true;
                        break;
                    } else {
                        out_line[i] = RxBuff[0];
                    }
                    i++;
                    (*line_len) = i;
                } else {
                    res = false;
                    break;
                }
            } else {
                res = false;
                break;
            }

            if(size <= i) {
                LOG_ERROR(FAT_FS, "OverRun: Size:%u,i:%u", size, i);
                res = false;
                break;
            }
        }

        if(line_len) {
            *line_len = i;
        }
    } else {
        LOG_ERROR(FAT_FS, "NodeErr:0x%p", FileNode);
    }

    return res;
}

bool fat_fs_cat(char* file_name) {
    bool res = false;
    FIL File = {0};
    FRESULT ret;
    ret = f_open(&File, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
    if(FR_OK == ret) {
        res = true;
        LOG_DEBUG(FAT_FS, "OpenOk [%s]", file_name);
        char RxBuff[2] = {0};
        uint32_t read_cnt = 0;
        while(1) {
            ret = f_read(&File, RxBuff, 1, (UINT*)&read_cnt);
            if(FR_OK == ret) {
                if(1 == read_cnt) {
                    cli_printf("%c", RxBuff[0]);
                } else {
                    break;
                }
            }
        }
        ret = f_close(&File);
        res = FatFsRet2Res(ret, "Close");
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "Open[%s]Err %u=%s", file_name, ret, FatFsRes2Str(ret));
#endif
    }
    return res;
}

bool FatFsRet2Res(FRESULT ret, const char* const prefix) {
    bool res = false;
    if(FR_OK == ret) {
        res = true;
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "%sErr %u=%s", prefix, ret, FatFsRes2Str(ret));
#endif
    }
    return res;
}

bool fat_fs_save_array(const char* const file_name, const uint8_t* const array, size_t size) {
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
                              FatFsRes2Str(ret));
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
                        LOG_ERROR(FAT_FS, "Write,Err[%s],ret:%u=%s", file_name, ret, FatFsRes2Str(ret));
#endif
                    }
                }

                ret = f_close(&File);
                res = FatFsRet2Res(ret, "Close") && res;
            } else {
#ifdef HAS_FAT_FS_DIAG
                LOG_ERROR(FAT_FS, "Open[%s]Err:%d=%s", file_name, ret, FatFsRes2Str(ret));
#endif
            }
        }
    }
    return res;
}

/*
 * text must be in RAM
 */
bool fat_fs_write(const char* const file_name, char* const text) {
    bool res = false;
    LOG_DEBUG(FAT_FS, "File:[%s],text:[%s]", file_name, text);
    static bool rec_prot = false;
    if(false == rec_prot) {
        rec_prot = true;

        uint32_t wr_len = 0;
        wr_len = strlen(text);
        strcat(text, CRLF);
        wr_len += 2;
        res = fat_fs_save_array(file_name, (const uint8_t* const)text, (size_t)wr_len);
        rec_prot = false;
    }

#if 0
        FRESULT ret = FR_INT_ERR;
        ret = f_open(&File, (const TCHAR*)file_name, FA_WRITE | FA_OPEN_ALWAYS | FA_READ);
        if(FR_OK == ret) {
            LOG_DEBUG(FAT_FS, "Open [%s] Ok", file_name);
            DWORD file_size = f_size(&File);
            ret = f_lseek(&File, file_size);
            if(FR_OK == ret) {
                LOG_DEBUG(FAT_FS, "MoveToEndOk [%s] size %u", file_name, file_size);
            } else {
                LOG_ERROR(FAT_FS, "MoveToEndErr [%s] size %u", file_name, file_size);
            }
            uint32_t write_cnt = 0;
            ret = f_write(&File, text, wr_len, (UINT*)&write_cnt);
            if(FR_OK == ret) {
                if(wr_len == write_cnt) {
                    LOG_DEBUG(FAT_FS, "WriteOk [%s] [%s] [%u] byte", file_name, text, wr_len);
                    res = true;
                } else {
                    LOG_ERROR(FAT_FS, "WriteDiff %u %u", wr_len, write_cnt);
                    res = false;
                }
            } else {
#ifdef HAS_FAT_FS_DIAG
                LOG_ERROR(FAT_FS, "WriteErr %s Byte %u %s", file_name, wr_len, FatFsRes2Str(ret));
#endif
            }

            ret = f_close(&File);
            res = FatFsRet2Res(ret,"Close") && res;

        } else {
#ifdef HAS_FAT_FS_DIAG
            LOG_ERROR(FAT_FS, "OpenErr %u=%s,File:%s", ret, FatFsRes2Str(ret), file_name);
#endif
        }
#endif

    return res;
}

bool fat_fs_save_double(const char* const file_name, double value) {
    bool res = false;
    char text[80] = "";
    snprintf(text, sizeof(text), "%f", value);
    res = fat_fs_write(file_name, text);
    if(false == res) {
        LOG_ERROR(FAT_FS, "WriteErr File: %s, Value:%f", file_name, value);
    }
    return res;
}

bool fat_fs_scan_light(const char* const path) {
    bool res = false;
    DIR dir = {0};
    FRESULT ret = FR_INT_ERR;
    ret = f_opendir(&dir, path);
    if(FR_OK == ret) {
        FILINFO fno = {0};
        for(;;) {

            ret = f_readdir(&dir, &fno); /* Read a directory item */
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
        LOG_ERROR(FAT_FS, "OpenDirErr:%d=%s", ret, FatFsRes2Str(ret));
#endif
        res = false;
    }
    return res;
}

int32_t fat_fs_file_line_cnt(const char* const file_name) {
    LOG_INFO(SYS, "CntLines,File:[%s]", file_name);

    int32_t line_cnt = 0; // Line line_cnter (result)

    FIL File = {0};
    FRESULT ret = f_open(&File, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
    if(FR_OK == ret) {
        DWORD size_bytes = f_size(&File);
        DWORD cur_size = 0;
        DWORD prev_pp = 0;
        LOG_INFO(FAT_FS, "OpenOk[%s],Size:%u Bytes", file_name, size_bytes);
        for(;;) {
            uint8_t buff[2] = {0};
            UINT ByteRead = 0;
            ret = f_read(&File, buff, 1, &ByteRead);
            if(FR_OK == ret) {
                if(1 == ByteRead) {
                    if('\n' == buff[0]) {
                        line_cnt++;
                    }
                    cur_size++;
                } else {
                    // line_cnt = -1;
                    break;
                }
            } else {
                // line_cnt = -1;
                break;
            }
            DWORD cur_pp = 100 * cur_size / size_bytes;
            if(prev_pp < cur_pp) {
                cli_printf("\rProg:%7u/%7u,%3u %%,line:%6d", cur_size, size_bytes, cur_pp, line_cnt);
            }
            prev_pp = cur_pp;

            // add progress
        }
        ret = f_close(&File);
        FatFsRet2Res(ret, "Close");

        LOG_DEBUG(SYS, "The file [%s] has %d lines", file_name, line_cnt);
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "Open[%s]Err:%d=%s", file_name, ret, FatFsRes2Str(ret));
#endif
        line_cnt = -1;
    }
    return line_cnt;
}

/*
 * https://irtos.sourceforge.net/FAT32_ChaN/doc/en/size.html
 * */
int32_t fat_fs_file_get_size(const char* const file_name) {
    int32_t fize_size = -1;
    FIL File = {0};
    FRESULT ret = f_open(&File, (const TCHAR*)file_name, FA_READ | FA_OPEN_EXISTING);
    if(FR_OK == ret) {
        LOG_DEBUG(FAT_FS, "OpenOk [%s]", file_name);
        DWORD size_bytes = f_size(&File);
        fize_size = (int32_t)size_bytes;
        ret = f_close(&File);
        FatFsRet2Res(ret, "Close");
    } else {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(FAT_FS, "Open[%s]Err:%d=%s", file_name, ret, FatFsRes2Str(ret));
#endif
    }
    return fize_size;
}

bool fat_fs_root(void) {
    bool res = false;
    res = fat_fs_scan_light("");
    return res;
}
