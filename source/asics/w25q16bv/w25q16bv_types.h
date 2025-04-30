#ifndef W25Q16BV_TYPES_H
#define W25Q16BV_TYPES_H


#include "std_includes.h"

#include "data_types.h"
#include "gpio_types.h"
#include "w25q16bv_const.h"
#include "w25q16bv_registers_types.h"

#define W25q16bv_COMMON_VARIABLES   \
    Pad_t chip_select;  \
    Pad_t reset;  \
    Pad_t write_protection;  \
    uint8_t spi_num;  \
    uint8_t num;  \
    bool valid;

typedef struct {
	W25q16bv_COMMON_VARIABLES
} W25q16bvConfig_t;

typedef struct {
	W25q16bv_COMMON_VARIABLES
} W25q16bvHandle_t;

typedef union {
    uint8_t byte[3];
    struct {
        uint32_t address : 24; /*bit0 write in progress bit*/
    } __attribute__((__packed__));
} __attribute__((__packed__)) W25Addr_t;

#endif /* W25Q16BV_TYPES_H */
