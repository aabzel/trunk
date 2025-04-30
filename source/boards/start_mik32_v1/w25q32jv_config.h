#ifndef W25Q32JV_CONFIG_H
#define W25Q32JV_CONFIG_H

#include "std_includes.h"
#include "w25q32jv_types.h"

#ifndef HAS_W25Q32JV
#error "+HAS_W25Q32JV"
#endif

extern const W25q32jvConfig_t W25q32jvConfig[];
extern W25q32jvHandle_t W25q32jvInstance[];

uint32_t w25q32jv_get_cnt(void);

#endif /* W25Q32JV_CONFIG_H */


