#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif /*HAS_SPI*/

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
#ifdef HAS_SPI1
    {
        .num = 1,
        .name = "SPI1",
        .bit_rate_hz = 200000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
        .irq_priority = 1,
        .valid = true,

    },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .name = "SPI2",
        .bit_rate_hz = 5000000, /*5000000<x<10000000*/
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
        .irq_priority = 1,
        .valid = true,

    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .name = "SPI3",
        .bit_rate_hz = 200000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
        .irq_priority = 1,
        .valid = true,

    },
#endif

#ifdef HAS_SPI4
    {
        .num = 4,
        .name = "SPI4",
        .bit_rate_hz = 200000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
        .irq_priority = 1,
        .valid = true,

    },
#endif
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI1
    {.num = 1, .valid = true},
#endif

#ifdef HAS_SPI2
    {.num = 2, .valid = true},
#endif

#ifdef HAS_SPI3
    {.num = 3, .valid = true},
#endif

#ifdef HAS_SPI4
    {.num = 4, .valid = true},
#endif
};

COMPONENT_GET_CNT(Spi, spi)
