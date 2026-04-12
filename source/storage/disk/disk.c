#include "disk.h"

#include "array_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "debug_info.h"
#include "fat_fs_types.h"
#include "interfaces_diag.h"
#include "log.h"

#ifdef HAS_STM32
#include "hal_diag.h"
#endif

#ifdef HAS_SW_SD_CARD
#include "sw_sd_card.h"
#endif

#ifdef HAS_SDIO
#include "sdio_mcal.h"
#endif

#ifdef HAS_SD_CARD
#include "sd_card_drv.h"
#endif

COMPONENT_GET_NODE(Disk, disk)
COMPONENT_GET_CONFIG(Disk, disk)

DRESULT disk_res_to_ret(const bool res) {
    DRESULT ret = RES_ERROR;
    if(res) {
        ret = RES_OK;
    }
    return ret;
}

DRESULT disk_ret_to_res(const DRESULT ret) {
    bool res = false;
    if(RES_OK == ret) {
        res = true;
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool DiskIsValidConfig(const DiskConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(DISK, "%u,NameErr", Config->num);
        }
    }
    return res;
}

bool disk_init_custom(void) {
    bool res = false;
    LOG_INFO(DISK, "Version:%s", DISK_VERSION);
    return res;
}

bool disk_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(DISK, "Proc:%u", num);
    DiskHandle_t* Node = DiskGetNode(num);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool disk_init_common(const DiskConfig_t* const Config, DiskHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {

            Node->block_size = Config->block_size;
            Node->num = Config->num;
            Node->inter_face = Config->inter_face;
            Node->name = Config->name;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool disk_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DISK, "DISK%u", num);
    const DiskConfig_t* Config = DiskGetConfig(num);
    if(Config) {
        res = DiskIsValidConfig(Config);
        if(res) {
#ifdef HAS_DISK_DIAG
            LOG_WARNING(DISK, "%s", DiskConfigToStr(Config));
#endif
            DiskHandle_t* Node = DiskGetNode(num);
            if(Node) {
                res = disk_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
            } else {
                LOG_ERROR(DISK, "DISK%u,NodeErr", num);
            }
        } else {
            LOG_ERROR(DISK, "DISK%u,ConfigErr", num);
        }
    } else {
        LOG_PARN(DISK, "DISK%u,ConfigErr", num);
    }
    return res;
}

/*
    Gets Time from RTC
    Time in DWORD
 */
DWORD get_fattime(void) {
    struct tm* stm = NULL;
    time_t t;
    t = time(0);
    stm = localtime(&t);

    FatFsTime_t FatFsTime = {0};

    FatFsTime.second = stm->tm_sec / 2;    /*Second / 2 (0..29, e.g. 25 for 50)*/
    FatFsTime.minute = stm->tm_min;        /*Minute (0..59)*/
    FatFsTime.hour = stm->tm_hour;         /*Hour (0..23)*/
    FatFsTime.day_of_month = stm->tm_mday; /*Day of the month (1..31)*/
    FatFsTime.month = stm->tm_mon + 1;     /*Month (1..12)*/
    FatFsTime.year = stm->tm_year - 80;    /*Year origin from the 1980 (0..127, e.g. 37 for 2017) */
    return ((DWORD)FatFsTime.dword);
}

//#include "hal_diag.h"

// extern Disk_drvTypeDef disk;

/**
 *             Gets Disk Status
 *      pdrv: Physical drive number (0..) Physical drive number to identify the drive
 *   DSTATUS: Operation status
 */
DSTATUS disk_status(BYTE pdrv) {
    LOG_DEBUG(DISK, "DISK%u,GetStatus", pdrv);
    DSTATUS stat = RES_OK;
#if 0
    stat = disk.drv[pdrv]->disk_status(disk.lun[pdrv]);
#endif
    return stat;
}

/**
 *             Reads Sector(s)
 *      pdrv: Physical drive number (0..)
 *      *buff: Data buffer to store read data
 *      sector: Sector address (LBA)
 *      count: Number of sectors to read (1..128)
 *   DRESULT: Operation result
 */
DRESULT disk_read(BYTE pdrv,    /* Physical drive nmuber to identify the drive */
                  BYTE* buff,   /* Data buffer to store read data */
                  DWORD sector, /* Sector address in LBA */
                  UINT count    /* Number of sectors to read */
) {
    DRESULT ret = RES_ERROR;
    bool res = false;
    (void)res;
    DiskHandle_t* Node = DiskGetNode((uint8_t)pdrv);
#ifdef HAS_INTERFACE_DIAG
    LOG_DEBUG(DISK, "DISK%u,ReadSector:%u,Cnt:%u,If:%s", pdrv, sector, count, InterfaceToStr(Node->inter_face));
#endif
    if(Node) {
        switch(Node->inter_face.interface_name) {
#ifdef HAS_SDIO
        case INTERFACE_NAME_SDIO: {
            res = sdio_read_sector(Node->if_num, (uint32_t)sector, (uint32_t)count, (uint8_t*)buff);
        } break;
#endif /**/

#ifdef HAS_SD_CARD
        case INTERFACE_NAME_SPI: {
            res = sd_read_sector( sector, (uint8_t* const)buff);
        } break;
#endif /**/

#ifdef HAS_SW_SD_CARD
        case INTERFACE_NAME_RAM: {
            res = disk_sw_read_sector(pdrv, sector, (uint8_t* const)buff);
        } break;
#endif
        default: {
            ret = RES_ERROR;
        } break;
        }
        log_level_t ll = log_level_get(DISK);
        if(LOG_LEVEL_DEBUG == ll) {
            print_hex(buff, Node->block_size);
        }
    }
    ret = disk_res_to_ret(res);
    log_res_u32(DISK, res, "ReadSector",sector);

    //log_write(ResToLogLevel(res), DISK, "DISK%u,ReadSector:%u,Cnt:%u", pdrv, sector, count);

    return ret;
}

/*
   Writes Sector(s)
       pdrv: Physical drive number (0..)
       *buff: Data to be written
       sector: Sector address (LBA)
       count: Number of sectors to write (1..128)
    DRESULT: Operation result
 */
#if _USE_WRITE == 1
DRESULT disk_write(BYTE pdrv,        /* Physical drive nmuber to identify the drive */
                   const BYTE* buff, /* Data to be written */
                   DWORD sector,     /* Sector address in LBA */
                   UINT count        /* Number of sectors to write */
) {
    DRESULT ret = RES_ERROR;
    bool res = false;
    LOG_DEBUG(DISK, "DISK%u,WriteSector:%u,SectorCnt:%u", pdrv, sector, count);
    DiskHandle_t* Node = DiskGetNode((uint8_t)pdrv);
    if(Node) {
        log_level_t ll = log_level_get(DISK);
        if(LOG_LEVEL_DEBUG == ll) {
            print_hex(buff, Node->block_size);
        }
        switch(Node->inter_face.interface_name) {
#ifdef HAS_SW_SD_CARD
        case INTERFACE_NAME_RAM: {
            res = disk_sw_write_sector(pdrv, sector, (uint8_t* const)buff);
        } break;
#endif

#ifdef HAS_SDIO
        case INTERFACE_NAME_SDIO: {
            res = sdio_write_sector(SD_CARD_SDIO_NUM, (uint32_t)sector, (uint32_t)count, (const uint8_t* const)buff);
        } break;
#endif /*HAS_SDIO*/

#ifdef HAS_SD_CARD
        case INTERFACE_NAME_SPI: {
            res = sd_write_sector(sector, (const uint8_t*)buff);
        } break;
#endif /*HAS_SPI*/
        default:
            ret = RES_ERROR;
            break;
        }
    }

    ret = disk_res_to_ret(res);
    //log_write(ResToLogLevel(res), DISK, "DISK%u,WriteSector:%u,Cnt:%u", pdrv, sector, count);

    return ret;
}
#endif /* _USE_WRITE == 1 */

#ifdef HAS_SDIO
/*
  pdrv,  Physical drive nmuber (0..)
  cmd,  Control code
  buff  Buffer to send/receive control data
  */
static DRESULT disk_sdio_ioctl(const BYTE pdrv, const BYTE cmd, void* const buff) {
    DRESULT ret = RES_ERROR;
    DiskHandle_t* Node = DiskGetNode((uint8_t)pdrv);
    if(Node) {
        ret = sdio_ioctl(Node->if_num, cmd, buff);
    }
    return ret;
}
#endif

/*
       I/O control operation
       pdrv: Physical drive number (0..)
       cmd: Control code
       *buff: Buffer to send/receive control data
    DRESULT: Operation result
 */
#if _USE_IOCTL == 1
DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff) {
    DRESULT ret = RES_ERROR;
    bool res = false;
    (void) res;
#ifdef HAS_DISK_DIAG
    LOG_DEBUG(DISK, "DISK%u,IoCtl,Cmd:%u=%s", pdrv, cmd, DiskIoCtlCmdToStr(cmd));
#endif
    DiskHandle_t* Node = DiskGetNode((uint8_t)pdrv);
    if(Node) {
        switch(Node->inter_face.interface_name) {
#ifdef HAS_SDIO
        case INTERFACE_NAME_SDIO: {
            ret = disk_sdio_ioctl(pdrv, cmd, buff);
        } break;
#endif

#ifdef HAS_SD_CARD
        case INTERFACE_NAME_SPI: {
            ret = sd_disk_ioctl(Node->inter_face.num, (uint8_t)cmd, (uint8_t*)buff);
        } break;
#endif

#ifdef HAS_SW_SD_CARD
        case INTERFACE_NAME_RAM: {
            ret = sd_sw_diskctl(Node->inter_face.num, (uint8_t)cmd, (uint8_t*)buff);
        } break;
#endif
        default:
            break;
        }
    }

#ifdef HAS_DISK_DIAG
    //res = disk_ret_to_res(ret);
    //log_write(ResToLogLevel(res), DISK, "DISK%u,IoCtl,Cmd:%u=%s", pdrv, cmd, DiskIoCtlCmdToStr(cmd));
#endif
    return ret;
}

#endif /* _USE_IOCTL == 1 */

/*
    num: Physical drive number to identify the drive (0..)
    DSTATUS: Operation status
 */
DSTATUS disk_initialize(BYTE num) {
    LOG_DEBUG(DISK, "DISK%u,Init", num);
    DSTATUS ret = 0;
    bool res = disk_init_one(num);
    ret = disk_res_to_ret(res);
#if 0
    if(disk.is_initialized[pdrv] == 0) {
      disk.is_initialized[pdrv] = 1;
      stat = disk.drv[pdrv]->disk_initialize(disk.lun[pdrv]);
    }
#endif
    return ret;
}

COMPONENT_INIT_PATTERT(DISK, DISK, disk)
COMPONENT_PROC_PATTERT(DISK, DISK, disk)
