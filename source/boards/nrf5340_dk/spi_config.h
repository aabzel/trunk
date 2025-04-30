#ifndef SPI_CONFIG_GENERAL_H
#define SPI_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "spi_types.h"

#ifndef HAS_SPI
#error "+ HAS_SPI"
#endif

#ifndef HAS_GPIO
#error "+ HAS_GPIO"
#endif

#ifndef HAS_MCU
#error "+ HAS_MCU"
#endif

extern SpiConfig_t SpiConfig[];
extern SpiHandle_t SpiInstance[];

uint32_t spi_get_cnt(void);

#endif /* SPI_CONFIG_GENERAL_H  */
