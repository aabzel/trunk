#ifndef FLASH_FS_CONFIG_H
#define FLASH_FS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_fs_types.h"

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif /*HAS_FLASH_FS*/

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define MEMORY_MANAGER1_OFFSET NVS_START
#define MEMORY_MANAGER1_LENGTH NVS_SECTOR_SIZE

#define MEMORY_MANAGER2_OFFSET (NVS_START+NVS_SECTOR_SIZE)
#define MEMORY_MANAGER2_LENGTH  NVS_SECTOR_SIZE

const extern FlashFsConfig_t FlashFsConfig;
extern FlashFs_t FlashFs;

#endif /* FLASH_FS_CONFIG_H  */
