#ifndef AT24CXX_TYPES_H
#define AT24CXX_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "at24cxx_const.h"
#include "gpio_types.h"

#define AT24CXX_COMMON_VARIABLES                                                                                       \
    uint8_t num;                                                                                                       \
    uint8_t i2c_num;                                                                                                   \
    uint8_t chip_addr;                                                                                                 \
    bool valid;                                                                                                        \
    bool write_enable;                                                                                                 \
    Pad_t wp;                                                                                                          \
    At24cChipModel_t chip_model;

typedef struct {
    AT24CXX_COMMON_VARIABLES
} At24cxxConfig_t;

typedef struct {
    AT24CXX_COMMON_VARIABLES
    uint32_t read_bytes;  /**/
    uint32_t write_bytes; /**/
} At24cxxHandle_t;

typedef struct {
    At24cChipModel_t chip_model;
    uint32_t capacity_bytes;
    bool valid;
    uint8_t pages;
    uint8_t page_size; /*Bytes*/
    uint8_t addr_bit;  /*internal address size*/
} At24cxxInfo_t;

#endif /* AT24CXX_TYPES_H */
