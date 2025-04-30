#include "spi_config.h"

#include "data_utils.h"
#include "spi_types.h"

//#include "c_defines_generated.h"

const SpiConfig_t SpiConfig[] = {
#ifdef HAS_SPI1
    {
        .num = 1,
        .name = "SPI1",
        .frame_size = 8,
        .bit_rate_hz = 2000000,
        .tx_mode = SPI_TX_FULL_DUPLEX,
        .valid = true,
        .interrupt_on = true,
        .move_mode = MOVE_MODE_INTERRUPT,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
        .irq_priority = 0,
    },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .frame_size = 8,
        .tx_mode = SPI_TX_FULL_DUPLEX,
        .name = "SPI2",
        .bit_rate_hz = 2000000,
        .valid = true,
           .move_mode = MOVE_MODE_INTERRUPT,
        .interrupt_on = true,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
         .irq_priority = 0,
    },
#endif


#ifdef HAS_SPI3
    {
        .num = 3,
        .tx_mode = SPI_TX_FULL_DUPLEX,
        .name = "SPI3",
        .frame_size = 8,
        .bit_rate_hz = 2000000,
        .valid = true,
        .interrupt_on = true,
           .move_mode = MOVE_MODE_INTERRUPT,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_PHASE_0,
         .irq_priority = 0,
    },
#endif

#ifdef HAS_SPI4
    {
        .num = 4,
        .bit_order = SPI_MOST_SIGNIFICANT_BIT_FIRST,
        .bit_rate_hz = 200000,//2000000
        .bus_role = IF_BUS_ROLE_MASTER,
        .chip_select = SPI_CHIP_SEL_SW,
        .frame_size = 8,
        .interrupt_on = true,
        .irq_priority = 0,
        .move_mode = MOVE_MODE_INTERRUPT,
        .name = "SPI4", // For SPI-Flash/ LIS3DH
        .phase = SPI_PHASE_0,
        .polarity = SPI_POLARITY_LATCH_RISING,
      //.PadCs = { .port = PORT_E, .pin = 11,},
        .PadSck = { .port = PORT_E, .pin = 2,},
        .PadMiso = { .port = PORT_D, .pin = 0,},
        .PadMosi = { .port = PORT_E, .pin = 6,},
       // .GpioRxDebug = { .port = PORT_C, .pin = 0,},
       // .GpioTxDebug = { .port = PORT_C, .pin = 4,},
        .tx_mode = SPI_TX_FULL_DUPLEX, //SPI_TX_HALF_DUPLEX_TX,
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
