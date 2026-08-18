#ifndef BH1750_TYPES_H
#define BH1750_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "bh1750_const.h"
#include "bh1750_dep.h"
#include "data_types.h"

#define BH1750_COMMON_VAR                                                                                             \
    uint8_t num;                                                                                                      \
    uint8_t i2c_num;                                                                                                  \
    uint8_t chip_addr;                                                                                                \
    bool valid;

typedef struct {
    BH1750_COMMON_VAR
#ifdef HAS_LOG
	char* name;
#endif
} Bh1750Config_t;

typedef struct {
    BH1750_COMMON_VAR
    uint32_t err_cnt;
    uint16_t word;
    DoubleValue_t lx;
    bool init;
} Bh1750Handle_t;

#endif /* BH1750_TYPES_H */
