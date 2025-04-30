#ifndef SPI_CONFIG_GENERAL_H
#define SPI_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "spi_types.h"

extern const SpiConfig_t SpiConfig[];
extern SpiHandle_t SpiInstance[];

uint32_t spi_get_cnt(void);

#endif /* SPI_CONFIG_GENERAL_H  */
