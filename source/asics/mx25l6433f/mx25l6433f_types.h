#ifndef MX25L6433F_TYPES_H
#define MX25L6433F_TYPES_H

#include "std_includes.h"
#include "data_types.h"
#include "gpio_types.h"
#include "mx25l6433f_const.h"
#include "mx25l6433f_registers_types.h"

#define MX25L6433F_COMMON_GPIO_VARIABLES               \
    Pad_t chip_select;                                 \
    Pad_t write_protection;                            \
    Pad_t reset;

#define MX25L6433F_COMMON_VARIABLES     \
    MX25L6433F_COMMON_GPIO_VARIABLES    \
    bool valid;                         \
    uint8_t num;                        \
    uint8_t spi_num;                    \
    char* name;

typedef struct {
    MX25L6433F_COMMON_VARIABLES
} Mx25l6433fConfig_t;

typedef struct {
    MX25L6433F_COMMON_VARIABLES
    Mx25l6433fRegStatus_t status;
    U32Value_t write_time_ms;
    Mx25l6433fRegConfiguration_t configuration;
    Mx25l6433fRegIdentification_t identification;
    uint32_t error_counter; /* Number of communication errors */
    uint32_t read_counter;  /* Bytes read since init */
    uint32_t write_counter; /* Bytes written since init */
    uint8_t electronic_signature;
    uint32_t spin;
    bool init;
} Mx25l6433fHandle_t;

typedef union {
    uint8_t byte[3];
    struct {
        uint32_t address : 24; /*bit0 write in progress bit*/
    } __attribute__((__packed__));
} __attribute__((__packed__)) Mx25Addr_t;

#endif /* MX25L6433F_TYPES_H */
