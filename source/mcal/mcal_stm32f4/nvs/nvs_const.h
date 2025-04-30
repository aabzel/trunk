#ifndef NVS_CONST_H
#define NVS_CONST_H

#include "flash_config.h"
#include "flash_mcal.h"

//#define FLASH_FS_PAGE_SIZE (FILE_SYS_SIZE / 2)
//#define NVS_SIZE (2 * FLASH_FS_PAGE_SIZE) /*Must be double multiple of FLASH_SECTOR_SIZE*/
//#define NVS_SIZE_PAGES (NVS_SIZE / FLASH_SECTOR_SIZE)
///* We should not touch the last flash memory sector.
// *
// * The last flash memory sector must contain a Customer Configuration section (CCFG)
// * that is used by boot ROM and TI provided drivers to configure the device.*/
//#define NVS_FLASH_START (FILE_SYS_START)
//#define NVS_FLASH_END (NVS_FLASH_START + NVS_SIZE - 1)

#endif /* NVS_CONST_H */
