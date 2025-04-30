#ifndef FLASH_FS_CONFIG_H
#define FLASH_FS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_fs_types.h"

#ifndef HAS_NVS
#error "+HAS_NVS"
#endif

#include "nvs_config.h"

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif /*HAS_FLASH_FS*/

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define FLASH_FS_PAGE_SIZE ((NVS_SIZE) / 2)
//#define NVS_SIZE (2 * FLASH_FS_PAGE_SIZE) /*Must be double multiple of FLASH_SECTOR_SIZE*/
#define NVS_SIZE_PAGES (NVS_SIZE / FLASH_SECTOR_SIZE)
/* We should not touch the last flash memory sector.
 *
 * The last flash memory sector must contain a Customer Configuration section (CCFG)
 * that is used by boot ROM and TI provided drivers to configure the device.*/
#define NVS_FLASH_END (NVS_START + NVS_SIZE - 1)

#define MEMORY_MANAGER1_OFFSET NVS_START
#define MEMORY_MANAGER1_LENGTH FLASH_FS_PAGE_SIZE

#define MEMORY_MANAGER2_OFFSET (NVS_START + FLASH_FS_PAGE_SIZE)
#define MEMORY_MANAGER2_LENGTH FLASH_FS_PAGE_SIZE

const extern FlashFsConfig_t FlashFsConfig;
extern FlashFs_t FlashFs;

#endif /* FLASH_FS_CONFIG_H  */
