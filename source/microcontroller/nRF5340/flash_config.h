#ifndef FLASH_CONFIG_GENERAL_H
#define FLASH_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "flash_types.h"
#include "nrf5340_app_const.h"
#ifdef HAS_FLASH_CUSTOM
#include "flash_custom_const.h"
#endif

#ifdef HAS_NVS
#include "nvs_config.h"
#endif

#ifndef HAS_FLASH
#error "Add HAS_FLASHER"
#endif /*HAS_FLASHER*/

#ifdef HAS_CORE_APP
#define APP_START_ADDRESS     FLASH_START_APP_CORE
#define APP_SIZE              FLASH_SIZE_APP_CORE
#endif

#ifdef HAS_CORE_NET
#define APP_START_ADDRESS     FLASH_START_NET_CORE
#define APP_SIZE              FLASH_SIZE_NET_CORE
#endif

#ifndef MBR_START_ADDRESS
#define MBR_START_ADDRESS APP_START_ADDRESS
#endif

extern FlashHandle_t FlashInstance;
extern const FlashConfig_t FlashConfig;
const extern FlashSectorConfig_t FlashSectorConfig[];

uint32_t flash_get_sector_cnt(void);

#endif /* FLASH_CONFIG_GENERAL_H  */
