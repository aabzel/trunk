#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SECTION_CFG_DATA SpiConfig[] = {
    {
        .num = 3,
        .frame_size = 8,
        .name = "SPI3",
        .bit_rate_hz = 5000000,//24000000 - error
        .bit_order = BIT_ORDER_MSB,
        .bus_role = BUS_ROLE_MASTER ,
        .tx_mode = SPI_TX_FULL_DUPLEX ,
        .direction = SPI_DIRECTION_2WIRES ,
        .move_mode = MOVE_MODE_INTERRUPT ,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .phase = SPI_CLK_IDLE_LEVEL_0,
        .irq_priority = 1,
        .valid = true,
        .interrupt_on = true,

        .PadSck =
            {
                .port = PORT_C,
                .pin = 10,
            },

        .PadMosi =
            {
                .port = PORT_C,
                .pin = 12,
            },
        .PadMiso =
            {
                .port = PORT_C,
                .pin = 11,
            },
    },
#ifdef HAS_SPI5
   {.num=5,
    .frame_size=8,
    .bus_role=BUS_ROLE_MASTER,
    .tx_mode=SPI_TX_FULL_DUPLEX,
    .bit_rate_hz=2000000,
    .move_mode=MOVE_MODE_INTERRUPT,
    .bit_order=BIT_ORDER_MSB,
    .direction=SPI_DIRECTION_2WIRES,
    .polarity=SPI_POLARITY_LATCH_RISING,
    .phase=SPI_CLK_IDLE_LEVEL_0,
    .chip_select=SPI_CHIP_SEL_SW,
    .name="NRF24L01P",
    .interrupt_on=true,
    .irq_priority=4,
    .valid=true
   },
#endif
};

SpiHandle_t SpiInstance[] = {
    {.num = 3, .valid = true},
#ifdef HAS_SPI5
    {.num=5, .valid=true},
#endif
};

COMPONENT_GET_CNT(Spi, spi)

