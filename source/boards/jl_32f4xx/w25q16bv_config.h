#ifndef W25Q16BV_CONFIG_H
#define W25Q16BV_CONFIG_H

#include "std_includes.h"
#include "w25q16bv_types.h"

#ifndef HAS_W25Q16BV
#error "+HAS_W25Q16BV"
#endif

extern const W25q16bvConfig_t W25q16bvConfig[];
extern W25q16bvHandle_t W25q16bvInstance[];

uint32_t w25q16bv_get_cnt(void);

#endif /* W25Q16BV_CONFIG_H */


