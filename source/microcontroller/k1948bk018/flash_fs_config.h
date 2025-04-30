#ifndef FLASH_FS_CONFIG_H
#define FLASH_FS_CONFIG_H

#include "std_includes.h"
#include "flash_fs_types.h"
#include "nvs_config.h"

#ifndef HAS_FLASH_FS
#error "Add HAS_FLASH_FS"
#endif /*HAS_FLASH_FS*/

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#define FLASH_FS_PAGE_SIZE ((NVS_SIZE) / 2)

#define FLASH_FS_1_OFFSET NVS_START
#define FLASH_FS_1_LENGTH FLASH_FS_PAGE_SIZE

#define FLASH_FS_2_OFFSET (NVS_START + FLASH_FS_PAGE_SIZE)
#define FLASH_FS_2_LENGTH FLASH_FS_PAGE_SIZE

extern const FlashFsConfig_t FlashFsConfig;
extern FlashFs_t FlashFs;

#endif /* FLASH_FS_CONFIG_H  */
