#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif /*HAS_SPI*/

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
   {.num=3, .name="SD", .bit_rate_hz=2000000, .valid=true},
};

SpiHandle_t SpiInstance[] = {
    {.num=3, .valid=true},
};

COMPONENT_GET_CNT(Spi, spi)

