#include "fat_fs_diag.h"

#include <stdio.h>
#include <string.h>

#include "diskio.h"
#include "fat_fs_diag.h"
#include "ff.h"
#include "log.h"
#include "macro_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* FatFsFileAttr2Str(BYTE fattrib) {
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
const char* FatFormatOptions2Str(BYTE format_opt) {
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

const char* FatFsRes2Str(FRESULT code) {
    const char* name = "?";
    switch(code) {
    case FR_OK:
        name = "Ok";
        break;
    case FR_DISK_ERR:
        name = "DiskErr";
        break;
    case FR_INT_ERR:
        name = "IntErr";
        break;
    case FR_NOT_READY:
        name = "NotReady";
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
    case FR_NO_FILESYSTEM:
        name = "NoFileSys";
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
    }
    return name;
}

const char* DiskCmd2Str(uint8_t cmd) {
    const char* name = "?";
    switch(cmd) {
    case CTRL_SYNC:
        name = "CtrlSync";
        break;
    case GET_SECTOR_COUNT:
        name = "GetSectorCount";
        break;
    case GET_SECTOR_SIZE:
        name = "GET_SECTOR_SIZE";
        break;
    case GET_BLOCK_SIZE:
        name = "GET_BLOCK_SIZE";
        break;
    case CTRL_TRIM:
        name = "CTRL_TRIM";
        break;
    case CTRL_POWER:
        name = "CTRL_POWER";
        break;
    case ATA_GET_SN:
        name = "ATA_GET_SN";
        break;
    case ATA_GET_MODEL:
        name = "ATA_GET_MODEL";
        break;
    case ATA_GET_REV:
        name = "ATA_GET_REV";
        break;
    case MMC_GET_SDSTAT:
        name = "MMC_GET_SDSTAT";
        break;
    case MMC_GET_OCR:
        name = "MMC_GET_OCR";
        break;
    case MMC_GET_CID:
        name = "MMC_GET_CID";
        break;
    case MMC_GET_CSD:
        name = "MMC_GET_CSD";
        break;
    case MMC_GET_TYPE:
        name = "MMC_GET_TYPE";
        break;
    case CTRL_FORMAT:
        name = "CTRL_FORMAT";
        break;
    case CTRL_EJECT:
        name = "CTRL_EJECT";
        break;
    case CTRL_LOCK:
        name = "CTRL_LOCK";
        break;
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

const char* DiskIoCtlCmd2Str(uint8_t const ioctl_code) {
    const char* name = "?";
    switch(ioctl_code) {
        /* Generic command (Used by FatFs) */
    case CTRL_SYNC:
        name = "SYNC";
        break; /* Complete pending write process (needed at _FS_READONLY == 0) */
    case GET_SECTOR_COUNT:
        name = "GetMediaSize";
        break; /* Get media size (needed at _USE_MKFS == 1) */
    case GET_SECTOR_SIZE:
        name = "GetSectorSize";
        break; /* Get sector size (needed at _MAX_SS != _MIN_SS) */
    case GET_BLOCK_SIZE:
        name = "GetEraseBlockSize";
        break; /* Get erase block size (needed at _USE_MKFS == 1) */
    case CTRL_TRIM:
        name = "TRIM";
        break; /* Inform device that the data on the block of sectors is no longer used (needed at _USE_TRIM == 1) */
    case CTRL_POWER:
        name = "Get/SetPowerStatus";
        break; /* Get/Set power status */
    case CTRL_LOCK:
        name = "Lock/UnlockMediaRemoval";
        break; /* Lock/Unlock media removal */
    case CTRL_EJECT:
        name = "EjectMedia";
        break; /* Eject media */
    case CTRL_FORMAT:
        name = "CreatePhysicalFormatOnTheMedia";
        break; //    8    /* Create physical format on the media */
    case MMC_GET_TYPE:
        name = "GetCardType";
        break; /* Get card type */
    case MMC_GET_CSD:
        name = "GetCSD";
        break; /* Get CSD */
    case MMC_GET_CID:
        name = "GetCID";
        break; /* Get CID */
    case MMC_GET_OCR:
        name = "GetOCR";
        break; /* Get OCR */
    case MMC_GET_SDSTAT:
        name = "GetSdStatus";
        break; /* Get SD status */
    case ATA_GET_REV:
        name = "GetF/Wrevision";
        break; /* Get F/W revision */
    case ATA_GET_MODEL:
        name = "GetModelMame";
        break; /* Get model name */
    case ATA_GET_SN:
        name = "GetSerialMumber";
        break; /* Get serial number */
    default:
        name = "UndefIoCtl";
        break; /* */
    }
    return name;
}

bool fat_fs_scan(const char* const path) {
    bool res = false;
    DIR dir = {0};
    FRESULT ret = FR_INT_ERR;

    static const table_col_t cols[] = {
        {5, "Num"},  {9, "SizeB"}, {10, "SizekB"},  {8, "fdate"},  {8, "ftime"},
        {6, "attr"}, {11, "Attr"}, {14, "altname"}, {22, "fname"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char line_str[120] = {0};
    uint16_t num = 0;
    ret = f_opendir(&dir, path);
    if(FR_OK == ret) {
        FILINFO FileInfo = {0};
        for(;;) {
            ret = f_readdir(&dir, &FileInfo); /* Read a directory item */
            if(FR_OK == ret) {
                if(0 == FileInfo.fname[0]) {
                    break;
                }
                if('.' == FileInfo.fname[0]) {
                    continue;
                } else {
                    strcpy(line_str, TSEP);
                    snprintf(line_str, sizeof(line_str), "%s %7u " TSEP, line_str, FileInfo.fsize);
                    snprintf(line_str, sizeof(line_str), "%s %8.3f " TSEP, line_str, BYTES_2_KBYTES(FileInfo.fsize));
                    snprintf(line_str, sizeof(line_str), "%s 0x%04x " TSEP, line_str, FileInfo.fdate);
                    snprintf(line_str, sizeof(line_str), "%s 0x%04x " TSEP, line_str, FileInfo.ftime);
                    snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, FileInfo.fattrib);
                    snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str, FatFsFileAttr2Str(FileInfo.fattrib));
                    snprintf(line_str, sizeof(line_str), "%s %12s " TSEP, line_str, FileInfo.altname);
                    snprintf(line_str, sizeof(line_str), "%s %20s " TSEP, line_str, FileInfo.fname);

                    cli_printf(TSEP " %3u ", num);
                    cli_printf("%s" CRLF, line_str);
                    num++;

                    // if(0==(FileInfo.fattrib & AM_DIR)){
                    //    cli_printf("%s/%s"CRLF,path,FileInfo.fname);
                    //}
                }
            } else {
                break;
            }
        }
    } else {
        LOG_ERROR(FAT_FS, "OpenDirErr:%d=%s", ret, FatFsRes2Str(ret));
        res = false;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
