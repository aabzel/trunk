#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include <std_includes.h>

#include "macro_utils.h"
#include "nvs_types.h"
#include "sys_config.h"

#ifndef HAS_NVS
#error "Add HAS_NVS"
#endif /*HAS_NVS*/

#ifndef HAS_MICROCONTROLLER
#error "Add HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#define NVS_SECTOR_SIZE (4 * K_BYTES)
#define NVS_SIZE (8 * NVS_SECTOR_SIZE)
#define	NVS_START (ROM_END-(NVS_SIZE))
#define NVS_END (NVS_START+NVS_SIZE)

extern const NvsConfig_t NvsConfig;
extern NvsItem_t NvsItem;

#endif /* NVS_CONFIG_H  */
