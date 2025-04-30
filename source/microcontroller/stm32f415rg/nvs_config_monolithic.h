#ifndef NVS_MONOLITHIC_CONFIG_H
#define NVS_MONOLITHIC_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "macro_utils.h"
#include "nvs_types.h"

#define NVS_SECTOR_SIZE (128 * K_BYTES)
#define NVS_SIZE (2*NVS_SECTOR_SIZE)
#define	NVS_START 0x080C0000
#define NVS_END (NVS_START+NVS_SIZE)

extern const NvsConfig_t NvsConfig;
extern NvsItem_t NvsItem;

#endif /* NVS_MONOLITHIC_CONFIG_H  */
