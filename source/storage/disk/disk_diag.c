#include "disk_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* DiskCmdToStr(uint8_t cmd) {
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
    default: break;
    }
    return name;
}

const char* DiskIoCtlCmdToStr(uint8_t const ioctl_code) {
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

const char* DiskConfigToStr(const DiskConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* DiskNodeToStr(const DiskHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool disk_diag(void) {
    bool res = false;
    return res;
}
