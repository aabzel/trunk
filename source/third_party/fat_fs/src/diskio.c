#include "diskio.h"
/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2017        */
/*                                                                       */
/*   Portions COPYRIGHT 2017 STMicroelectronics                          */
/*   Portions Copyright (C) 2017, ChaN, all right reserved               */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various existing      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "array_diag.h"
#include "debug_info.h"
#include "ff_gen_drv.h"
#include "log.h"
#ifdef HAS_SDIO
#include "sdio_mcal.h"
#endif /*HAS_SDIO*/
#include "hal_diag.h"

#ifdef HAS_SD_CARD
#include "sd_card_drv.h"
#endif /*HAS_SPI*/

#ifdef HAS_FAT_FS_DIAG
#include "fat_fs_diag.h"
#endif

#if defined(__GNUC__)
#ifndef __weak
#define __weak __attribute__((weak))
#endif
#endif

extern Disk_drvTypeDef disk;

/**
 * @brief  Gets Disk Status
 * @param  pdrv: Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS disk_status(BYTE pdrv /* Physical drive number to identify the drive */
) {
    LOG_DEBUG(DISK, "DISK%u GetStatus", pdrv);
    DSTATUS stat = RES_OK;
#if 0
    stat = disk.drv[pdrv]->disk_status(disk.lun[pdrv]);
#endif
    return stat;
}

/**
 * @brief  Initializes a Drive
 * @param  pdrv: Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS disk_initialize(BYTE pdrv /* Physical drive nmuber to identify the drive */
) {
    LOG_DEBUG(DISK, "DISK%u Init", pdrv);
    DSTATUS stat = RES_OK;
#if 0
    if(disk.is_initialized[pdrv] == 0) {
      disk.is_initialized[pdrv] = 1;
      stat = disk.drv[pdrv]->disk_initialize(disk.lun[pdrv]);
    }
#endif
    return stat;
}

/**
 * @brief  Reads Sector(s)
 * @param  pdrv: Physical drive number (0..)
 * @param  *buff: Data buffer to store read data
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to read (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT disk_read(BYTE pdrv,    /* Physical drive nmuber to identify the drive */
                  BYTE* buff,   /* Data buffer to store read data */
                  DWORD sector, /* Sector address in LBA */
                  UINT count    /* Number of sectors to read */
) {
    DRESULT ret = RES_ERROR;
    bool res = false;
    (void)res;
    LOG_DEBUG(DISK, "DISK%u Read Sector %u, Cnt %u", pdrv, sector, count);
#ifdef HAS_SDIO
    res = sdio_read_sector(SD_CARD_SDIO_NUM, (uint32_t)sector, (uint32_t)count, (uint8_t*)buff);
#endif /*HAS_SDIO*/

#ifdef HAS_SD_CARD
    res = sd_read_sector(sector, (uint8_t* const)buff);
#endif /*HAS_SD_CARD*/
    if(res) {
        ret = RES_OK;
#ifdef HAS_ARRAY_DIAG
        log_level_t ll = log_level_get(DISK);
        if(LOG_LEVEL_DEBUG == ll) {
            print_hex(buff, BLOCK_SIZE_BYTE);
        }
#endif
    } else {
        ret = RES_ERROR;
        LOG_ERROR(DISK, "DISK%u ReadSector %u, Cnt %u Err", pdrv, sector, count);
    }
    return ret;
}

/**
 * @brief  Writes Sector(s)
 * @param  pdrv: Physical drive number (0..)
 * @param  *buff: Data to be written
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to write (1..128)
 * @retval DRESULT: Operation result
 */
#if _USE_WRITE == 1
DRESULT disk_write(BYTE pdrv,        /* Physical drive nmuber to identify the drive */
                   const BYTE* buff, /* Data to be written */
                   DWORD sector,     /* Sector address in LBA */
                   UINT count        /* Number of sectors to write */
) {
    LOG_DEBUG(DISK, "DISK%u WriteSector %u, Cnt %u", pdrv, sector, count);
#ifdef HAS_SD_CARD
    log_level_t ll = log_level_get(DISK);
    if(LOG_LEVEL_DEBUG == ll) {
        print_hex(buff, BLOCK_SIZE_BYTE);
    }
#endif
    DRESULT ret = RES_ERROR;
    bool res = false;
#ifdef HAS_SD_CARD
    res = sd_write_sector(sector, (const uint8_t*)buff);
#endif /*HAS_SPI*/

#ifdef HAS_SDIO
    res = sdio_write_sector(SD_CARD_SDIO_NUM, (uint32_t)sector, (uint32_t)count, (const uint8_t* const)buff);
#endif /*HAS_SDIO*/

    if(res) {
        LOG_DEBUG(DISK, "DISK%u WriteSectorOk %u, Cnt %u", pdrv, sector, count);
        ret = RES_OK;
    } else {
        ret = RES_ERROR;
        LOG_ERROR(DISK, "DISK%u WriteSectorErr %u, Cnt %u", pdrv, sector, count);
    }
    return ret;
}
#endif /* _USE_WRITE == 1 */

/**
 * @brief  I/O control operation
 * @param  pdrv: Physical drive number (0..)
 * @param  cmd: Control code
 * @param  *buff: Buffer to send/receive control data
 * @retval DRESULT: Operation result
 */
#if _USE_IOCTL == 1
DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
                   BYTE cmd,  /* Control code */
                   void* buff /* Buffer to send/receive control data */
) {
#ifdef HAS_FAT_FS_DIAG
    LOG_DEBUG(DISK, "DISK%u IoCtl Cmd:%u=%s", pdrv, cmd, DiskIoCtlCmd2Str(cmd));
#endif
    DRESULT ret = RES_NOTRDY;
#ifdef HAS_SDIO
#ifdef HAS_FAT_FS_DIAG
    LOG_DEBUG(LG_SDIO, "DiskIoCtrl Drv %u Cmd:%u=%s", pdrv, cmd, DiskCmd2Str(cmd));
#endif
    SdioHandle_t* SdioNode = SdioGetNode(1);
    if(SdioNode) {
        HAL_StatusTypeDef err;
        err = HAL_SD_GetCardInfo(&SdioNode->sdio_h, &SdioNode->CardInfo);
        if(HAL_OK == err) {
            switch(cmd) {
            case CTRL_SYNC: {
                ret = RES_OK;
            } break;
            case GET_SECTOR_COUNT: {
                LOG_DEBUG(DISK, "BlockNbr %u", SdioNode->CardInfo.BlockNbr);
                *((DWORD*)buff) = SdioNode->CardInfo.BlockNbr;
                ret = RES_OK;
            } break;
            case GET_SECTOR_SIZE: {
                LOG_DEBUG(DISK, "BlockSize %u", SdioNode->CardInfo.BlockSize);
                *((DWORD*)buff) = SdioNode->CardInfo.BlockSize;
                ret = RES_OK;
            } break;
            case GET_BLOCK_SIZE: {
                LOG_DEBUG(DISK, "GET_BLOCK_SIZE %u", SdioNode->CardInfo.BlockSize / SDIO_BLOCK_SIZE);
                *(DWORD*)buff = SdioNode->CardInfo.BlockSize / SDIO_BLOCK_SIZE;
                ret = RES_OK;
            } break;
            } // switch
        } else {
            LOG_ERROR(DISK, "HalErr %u=%s", err, HalStatus2Str(err));
        }
    }
#endif /*HAS_SDIO*/

#ifdef HAS_SD_CARD
    ret = sd_disk_ioctl(pdrv, (uint8_t)cmd, (uint8_t*)buff);
#endif /*HAS_SPI*/
    if(RES_OK != ret) {
#ifdef HAS_FAT_FS_DIAG
        LOG_ERROR(DISK, "DISK%u IoCtlErr Cmd:%u=%s", pdrv, cmd, DiskIoCtlCmd2Str(cmd));
#endif
    }

    return ret;
}
#endif /* _USE_IOCTL == 1 */

/**
 * @brief  Gets Time from RTC
 * @param  None
 * @retval Time in DWORD
 */
__weak DWORD get_fattime(void) { return 0; }
