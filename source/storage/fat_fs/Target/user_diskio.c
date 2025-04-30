/**
 * @file    user_diskio.c
 * @brief   This file includes a diskio driver skeleton to be completed by the
 * user.
 */

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/*
 * Warning: the user section 0 is no more in use (starting from CubeMx
 * version 4.16.0) To be suppressed in the future. Kept to ensure backward
 * compatibility with previous CubeMx versions when migrating projects. User
 * code previously added there should be copied in the new user sections before
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <string.h>

#include "ff_gen_drv.h"
#include "log.h"
#include "sd_card_driver.h"
#include "user_diskio.h"
#include "user_diskio_spi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS USER_status(BYTE pdrv);
DRESULT USER_read(BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
DRESULT USER_write(BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
DRESULT USER_ioctl(BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef USER_Driver = {
    USER_initialize, USER_status, USER_read,
#if _USE_WRITE
    USER_write,
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
    USER_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Initializes a Drive
 * @param  pdrv: Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS
USER_initialize(BYTE pdrv /* Physical drive number to identify the drive */
) {
  LOG_NOTICE(SYS, "%s()", __FUNCTION__);
  DSTATUS ret;
  ret = SD_disk_initialize(pdrv);
  return ret;
}

/**
 * @brief  Gets Disk Status
 * @param  pdrv: Physical drive number (0..)
 * @retval DSTATUS: Operation status
 */
DSTATUS USER_status(BYTE pdrv /* Physical drive number to identify the drive */
) {
  LOG_NOTICE(SYS, "%s()", __FUNCTION__);
  // return SD_disk_status(pdrv);
  return Stat;
}

/**
 * @brief  Reads Sector(s)
 * @param  pdrv: Physical drive number (0..)
 * @param  *buff: Data buffer to store read data
 * @param  sector: Sector address (LBA)
 * @param  count: Number of sectors to read (1..128)
 * @retval DRESULT: Operation result
 */
DRESULT USER_read(BYTE pdrv,  /* Physical drive nmuber to identify the drive */
                  BYTE *buff, /* Data buffer to store read data */
                  DWORD sector, /* Sector address in LBA */
                  UINT count    /* Number of sectors to read */
) {
  // LOG_NOTICE(SYS, "%s()", __FUNCTION__);
  /* USER CODE BEGIN READ */
  DRESULT ret = RES_ERROR;
  ret = SD_disk_read(pdrv, buff, sector, count);
  return ret;
  /* USER CODE END READ */
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
DRESULT USER_write(BYTE pdrv, /* Physical drive nmuber to identify the drive */
                   const BYTE *buff, /* Data to be written */
                   DWORD sector,     /* Sector address in LBA */
                   UINT count        /* Number of sectors to write */
) {
  LOG_NOTICE(SYS, "%s()", __FUNCTION__);
  DRESULT ret = RES_ERROR;
  ret = SD_disk_write(pdrv, buff, sector, count);
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
DRESULT USER_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
                   BYTE cmd,  /* Control code */
                   void *buff /* Buffer to send/receive control data */
) {
  LOG_NOTICE(SYS, "%s()", __FUNCTION__);
  DRESULT ret = RES_ERROR;
  ret = SD_disk_ioctl(pdrv, cmd, buff);
  return ret;
}
#endif /* _USE_IOCTL == 1 */
