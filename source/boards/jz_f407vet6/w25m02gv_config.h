#ifndef W25M02GV_CONFIG_H
#define W25M02GV_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#include "w25m02gv_types.h"

extern const W25m02gvConfig_t W25m02gvConfig[];
extern W25m02gvHandle_t W25m02gvInstance[];

uint32_t w25m02gv_get_cnt(void);

#endif /* W25M02GV_CONFIG_H */
