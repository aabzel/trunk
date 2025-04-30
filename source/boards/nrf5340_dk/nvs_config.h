#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "nvs_types.h"
#include "sys_config.h"

#define	NVS_START  (0x000fc000)
#define NVS_SIZE   (4*(ON_CHIP_NOR_FLASH_PAGE_SIZE))

#define	NVS_END  (NVS_START+NVS_SIZE)

extern const NvsConfig_t NvsConfig;
extern NvsItem_t NvsItem;

#endif /* NVS_CONFIG_H  */
