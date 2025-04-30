#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "nvs_types.h"


#define NVS_SECTOR_SIZE   (16 * K_BYTES)
#define NVS_SIZE   (2 * NVS_SECTOR_SIZE)
#define	NVS_START  (0x08008000)
#define NVS_END (NVS_START+NVS_SIZE)

#if 0
#define MEMORY_MANAGER1_OFFSET NVS_START
#define MEMORY_MANAGER1_LENGTH NVS_SECTOR_SIZE

#define MEMORY_MANAGER2_OFFSET (NVS_START+NVS_SECTOR_SIZE)
#define MEMORY_MANAGER2_LENGTH NVS_SECTOR_SIZE
#endif 

extern const NvsConfig_t NvsConfig;
extern NvsItem_t NvsItem;

#endif /* NVS_CONFIG_H  */
