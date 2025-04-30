#ifndef NVS_SEPARATE_CONFIG_H
#define NVS_SEPARATE_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "nvs_types.h"

#ifndef HAS_NVS
#error "Add HAS_NVS"
#endif /*HAS_NVS*/

#ifndef HAS_MICROCONTROLLER
#error "Add HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#ifdef HAS_GENERIC_MONOLITHIC
#include "nvs_config_monolithic.h"
#else
#define NVS_SECTOR_SIZE (16 * K_BYTES)
#define NVS_SIZE (2 * NVS_SECTOR_SIZE)
#define	NVS_START (0x08008000)
#define NVS_END (NVS_START+NVS_SIZE)
#endif

extern const NvsConfig_t NvsConfig;
extern NvsItem_t NvsItem;

#endif /* NVS_SEPARATE_CONFIG_H  */
