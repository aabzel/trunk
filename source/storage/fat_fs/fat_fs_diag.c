#include "fat_fs_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "disk.h"
#include "ff.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* FatFsFileAttrToStr(BYTE fattrib) {
    static char line_str[11] = {0};
    memset(line_str, 0, sizeof(line_str));
    strcpy(line_str, "...._....");
    if(AM_RDO == (fattrib & AM_RDO)) {
        line_str[8] = 'r';
    }
    if(AM_HID == (fattrib & AM_HID)) {
        line_str[7] = 'h';
    }
    if(AM_SYS == (fattrib & AM_SYS)) {
        line_str[6] = 's';
    }
    if(AM_DIR == (fattrib & AM_DIR)) {
        line_str[3] = 'd';
    }
    if(AM_ARC == (fattrib & AM_ARC)) {
        line_str[2] = 'a';
    }
    return line_str;
}

/* Format options (2nd argument of f_mkfs) */
const char* FatFormatOptionsToStr(BYTE format_opt) {
    const char* name = "?";
    switch(format_opt) {
    case FM_FAT:
        name = "FAT16";
        break;
    case FM_FAT32:
        name = "FAT32";
        break;
    case FM_EXFAT:
        name = "EXFAT";
        break;
    case FM_ANY:
        name = "ANY";
        break;
    case FM_SFD:
        name = "SFD";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* FatFsResToStr(FRESULT code) {
    const char* name = "?";
    switch(code) {
    case FR_NO_FILESYSTEM:
        name = "NoFileSys";
        break;
    case FR_OK:
        name = "Ok";
        break;
    case FR_NOT_READY:
        name = "NotReady";
        break;
    case FR_DISK_ERR:
        name = "DiskErr";
        break;
    case FR_INT_ERR:
        name = "IntErr";
        break;
    case FR_NO_FILE:
        name = "NoFile";
        break;
    case FR_NO_PATH:
        name = "NoPath";
        break;
    case FR_INVALID_NAME:
        name = "InvalName";
        break;
    case FR_DENIED:
        name = "Denied";
        break;
    case FR_EXIST:
        name = "Exist";
        break;
    case FR_INVALID_OBJECT:
        name = "InvalidObj";
        break;
    case FR_WRITE_PROTECTED:
        name = "WrProt";
        break;
    case FR_INVALID_DRIVE:
        name = "InvalDrive";
        break;
    case FR_NOT_ENABLED:
        name = "NotEnable";
        break;
    case FR_MKFS_ABORTED:
        name = "MkFsAbort";
        break;
    case FR_TIMEOUT:
        name = "TimeOut";
        break;
    case FR_LOCKED:
        name = "Lock";
        break;
    case FR_NOT_ENOUGH_CORE:
        name = "NotEnougthCore";
        break;
    case FR_TOO_MANY_OPEN_FILES:
        name = "ToManyOpen";
        break;
    case FR_INVALID_PARAMETER:
        name = "InvalidPar";
        break;
    default: break;
    }
    return name;
}

bool FatFsParseFileInfo(FILINFO* FileInfo) {
    bool res = false;
    if(FileInfo) {
        LOG_INFO(FAT_FS, "name:%s", FileInfo->fname);
        LOG_INFO(FAT_FS, "altname:%s", FileInfo->altname);
        LOG_INFO(FAT_FS, "size:%u", FileInfo->fsize);
        LOG_INFO(FAT_FS, "time:%u", FileInfo->ftime);
        LOG_INFO(FAT_FS, "date:%u", FileInfo->fdate);
        LOG_INFO(FAT_FS, "attrib:%u", FileInfo->fattrib);
        res = true;
    }
    return res;
}

bool fat_fs_scan(const char* const path) {
    bool res = false;

    static const table_col_t cols[] = {
        {5, "Num"},  {9, "SizeB"}, {10, "SizekB"},  {8, "fdate"},  {8, "ftime"},
        {6, "attr"}, {11, "Attr"}, {14, "altname"}, {22, "fname"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    FRESULT ret = FR_INT_ERR;
    DIR dir = {0};
    ret = f_opendir(&dir, path);
    if(FR_OK == ret) {
        uint16_t num = 0;
        for(;;) {
            FILINFO FileInfo = {0};
            ret = f_readdir(&dir, &FileInfo); /* Read a directory item */
            if(FR_OK == ret) {
                if(0 == FileInfo.fname[0]) {
                    break;
                }
                if('.' == FileInfo.fname[0]) {
                    continue;
                } else {
                    char line_str[120] = {0};
                    strcpy(line_str, TSEP);
                    snprintf(line_str, sizeof(line_str), "%s %7u " TSEP, line_str, FileInfo.fsize);
                    snprintf(line_str, sizeof(line_str), "%s %8.3f " TSEP, line_str, BYTES_2_KBYTES(FileInfo.fsize));
                    snprintf(line_str, sizeof(line_str), "%s 0x%04x " TSEP, line_str, FileInfo.fdate);
                    snprintf(line_str, sizeof(line_str), "%s 0x%04x " TSEP, line_str, FileInfo.ftime);
                    snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, FileInfo.fattrib);
                    snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str,
                             FatFsFileAttrToStr(FileInfo.fattrib));
                    snprintf(line_str, sizeof(line_str), "%s %12s " TSEP, line_str, FileInfo.altname);
                    snprintf(line_str, sizeof(line_str), "%s %20s " TSEP, line_str, FileInfo.fname);

                    cli_printf(TSEP " %3u ", num);
                    cli_printf("%s" CRLF, line_str);
                    num++;
                    res = true;
                    // if(0==(FileInfo.fattrib & AM_DIR)){
                    //    cli_printf("%s/%s"CRLF,path,FileInfo.fname);
                    //}
                }
            } else {
                break;
            }
        }
    } else {
        LOG_ERROR(FAT_FS, "OpenDirErr:%d=%s", ret, FatFsResToStr(ret));
        res = false;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

const char* FatFsConfigToStr(const FatFsConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* FatFsNodeToStr(const FatFsHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool fat_fs_diag(void) {
    bool res = false;
    return res;
}

const char* FatFsFileToStr(const FIL* const file) {
    if(file) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sflag:0x%x,", text, file->flag);
        snprintf(text, sizeof(text), "%serr:0x%x,", text, file->err);
        snprintf(text, sizeof(text), "%sfptr:%u,", text, file->fptr);
        snprintf(text, sizeof(text), "%ssect:%u,", text, file->sect);
        snprintf(text, sizeof(text), "%sclust:%u,", text, file->clust);
    }
    return text;
}
