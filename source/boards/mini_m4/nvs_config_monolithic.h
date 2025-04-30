#ifndef NVS_MONOLITHIC_CONFIG_H
#define NVS_MONOLITHIC_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"

#ifndef HAS_NVS
#error "Add HAS_NVS"
#endif /*HAS_NVS*/

#ifndef HAS_FLASH
#error "Add HAS_FLASH"
#endif /*HAS_FLASH*/

#define NVS_SECTOR_SIZE   (128 * K_BYTES)
#define NVS_SIZE   (2*NVS_SECTOR_SIZE)
#define	NVS_START  0x080c0000
#define NVS_END (NVS_START+NVS_SIZE)

#endif /* NVS_MONOLITHIC_CONFIG_H  */
