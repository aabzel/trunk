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
        .bit_rate_hz = 250000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .irq_priority = 1,
        .phase = SPI_PHASE_0,
        .valid = true,
    },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .name = "SPI2",
        .bit_rate_hz = 250000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .irq_priority = 1,
        .phase = SPI_PHASE_0,
        .valid = true,

        .PadSck =
            {
                .port = PORT_A,
                .pin = 9,
            },
        .PadMiso =
            {
                .port = PORT_A,
                .pin = 12,
            },
        .PadMosi =
            {
                .port = PORT_A,
                .pin = 10,
            },
    },
#endif

#ifdef HAS_SPI3
    {
        .num = 3,
        .name = "SPI3",
        .bit_rate_hz = 250000,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .irq_priority = 1,
        .phase = SPI_PHASE_0,
        .valid = true,

        .PadSck =
            {
                .port = PORT_C,
                .pin = 10,
            },

        .PadMiso =
            {
                .port = PORT_B,
                .pin = 4,
            },

        .PadMosi =
            {
                .port = PORT_C,
                .pin = 12,
            },
    },
#endif
};

SpiHandle_t SpiInstance[] = {
//{.num=1, .valid=true},
#ifdef HAS_SPI1
    {.num = 1, .valid = true},
#endif

#ifdef HAS_SPI2
    {.num = 2, .valid = true},
#endif
#ifdef HAS_SPI3
    {.num = 3, .valid = true},
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
