#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"

#ifndef HAS_NVS
#error "Add HAS_NVS"
#endif /*HAS_NVS*/

#ifndef HAS_MCU
#error "Add HAS_MCU"
#endif /*HAS_MCU*/

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#define NVS_SECTOR_SIZE   (16 * K_BYTES)
#define NVS_SIZE   (2 * NVS_SECTOR_SIZE)
#define	NVS_START  (0x08008000)
#define NVS_END (NVS_START+NVS_SIZE)

#define MEMORY_MANAGER1_OFFSET NVS_START
#define MEMORY_MANAGER1_LENGTH NVS_SECTOR_SIZE

#define MEMORY_MANAGER2_OFFSET (NVS_START+NVS_SECTOR_SIZE)
#define MEMORY_MANAGER2_LENGTH  NVS_SECTOR_SIZE


#endif /* NVS_CONFIG_H  */
