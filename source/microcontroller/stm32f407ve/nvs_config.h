#ifndef NVS_CONFIG_H
#define NVS_CONFIG_H

#include "std_inc.h"
#include "macro_utils.h"
#include "nvs_types.h"

#define NVS_SECTOR_SIZE   (16 * K_BYTES)
#define NVS_SIZE   (2 * NVS_SECTOR_SIZE)
#define	NVS_START  (0x08008000)
#define NVS_END (NVS_START+ NVS_SIZE)

extern const NvsConfig_t SECTION_CFG_DATA NvsConfig[];
extern NvsHandle_t NvsInstance[];

extern const uint8_t SECTION_NVRAM nvram_memory[NVS_SIZE];


uint32_t nvs_get_cnt(void);

#endif /* NVS_CONFIG_H  */
