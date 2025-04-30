#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif /*HAS_SPI*/

#include "data_utils.h"
#include "spi_types.h"

/*constant compile-time known settings*/
SpiConfig_t SpiConfig[] = {
#ifdef HAS_SPI2
    {
        .num = 2,
        .name = "SPI2",
        .irq_priority = 7,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .phase = SPI_PHASE_0,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .bit_rate_hz = 4000000,
        .chip_select = SPI_CHIP_SEL_SW,
        .PadSck = {.port = 0, .pin = 17},
        .PadMosi = {.port = 0, .pin = 13},
        .PadMiso = {.port = 0, .pin = 14},
        .valid = true,
    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .name = "SPI3",
        .irq_priority = 7,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .phase = SPI_PHASE_0,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .bit_rate_hz = 500000,
        .chip_select = SPI_CHIP_SEL_SW,
        .PadSck = {.port = 1, .pin = 15},
        .PadMiso = {.port = 1, .pin = 14},
        .PadMosi = {.port = 1, .pin = 13},
        .valid = true,
    },
#endif /*HAS_SPI3*/

#ifdef HAS_SPI4
    {
        .num = 4,
        .name = "SPI4",
        .irq_priority = 7,
#ifdef HAS_AD9833
        .polarity = SPI_POLARITY_LATCH_FALING,
        .phase = SPI_PHASE_1,
#else  /*HAS_AD9833*/
        .polarity = SPI_POLARITY_LATCH_RISING,
        .phase = SPI_PHASE_0,
#endif /*HAS_AD9833*/
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .bit_rate_hz = 1000000,
        .chip_select = SPI_CHIP_SEL_SW,
        .PadSck = {.port = 1, .pin = 15},
        .PadMiso = {.port = 1, .pin = 14},
        .PadMosi = {.port = 1, .pin = 13},
        .valid = true,
    },
#endif /*HAS_SPI4*/
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI2
    {
        .num = 2,
        .valid = true,
    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .valid = true,
    },
#endif

#ifdef HAS_SPI4
    {
        .num = 4,
        .valid = true,
    },
#endif
};

uint32_t spi_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SpiInstance);
    cnt2 = ARRAY_SIZE(SpiConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
