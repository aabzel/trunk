#ifndef MX25R6435F_TYPES_H
#define MX25R6435F_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "data_types.h"
#include "gpio_types.h"
#include "mx25r6435f_const.h"
#include "mx25r6435f_registers_types.h"

typedef struct {
    Pad_t chip_select;
    Pad_t reset;
    Pad_t write_protection;
    uint8_t spi_num;
} Mx25r6435fConfig_t;

typedef struct {
    RegStatus_t status;
    uint8_t electronic_signature;
    U32Value_t write_time_ms;
    RegConfiguration_t configuration;
    RegIdentification_t identification;
} Mx25r6435fHandle_t;

typedef union {
    uint8_t byte[3];
    struct {
        uint32_t address : 24; /*bit0 write in progress bit*/
    } __attribute__((__packed__));
} __attribute__((__packed__)) Mx25Addr_t;

#endif /* MX25R6435F_TYPES_H */
