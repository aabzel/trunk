#ifndef SW_NVRAM_CONFIG_H
#define SW_NVRAM_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sw_nvram_types.h"

#ifndef HAS_SW_NVRAM
#error  "+HAS_SW_NVRAM"
#endif /*HAS_SW_NVRAM*/

extern const NvRamConfig_t NvRamConfig[];
extern NvRamItem_t NvRamItem[];

uint32_t sw_nvram_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /*SW_NVRAM_CONFIG_H*/
