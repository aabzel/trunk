#ifndef SPI_CONFIG_GENERAL_H
#define SPI_CONFIG_GENERAL_H

#include "std_includes.h"
#include "spi_types.h"

extern const SpiConfig_t SpiConfig[];
extern SpiHandle_t SpiInstance[];

uint32_t spi_get_cnt(void);

#endif /* SPI_CONFIG_H  */
