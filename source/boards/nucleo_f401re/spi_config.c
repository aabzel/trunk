#include "spi_config.h"

#ifndef HAS_SPI
#error "Add HAS_SPI"
#endif

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
#ifdef HAS_SPI1
   {
           .num = 1,
           .name = "W25Q16",
           .bit_rate_hz = 250000,
           .bus_role = BUS_ROLE_MASTER,
           .frame_size =  8,
           .tx_mode = SPI_TX_FULL_DUPLEX,
           .move_mode = MOVE_MODE_INTERRUPT,
           .bit_order = BIT_ORDER_LSB,
           .polarity =  SPI_POLARITY_LATCH_FALING,
           .phase =  SPI_CLK_IDLE_LEVEL_1,
           .chip_select = SPI_CHIP_SEL_SW,
           .interrupt_on = true,
           .irq_priority =  0,
           .valid = true,
   },
#endif

#ifdef HAS_SPI2
    {
        .num = 2,
        .bit_order = BIT_ORDER_MSB, //BIT_ORDER_LSB LackOfAntiPattern:0xff,After:1025 try, // BIT_ORDER_MSB read R1=0x80,
        .direction = SPI_DIRECTION_2WIRES,
        .polarity = SPI_POLARITY_LATCH_RISING,
        .chip_select = SPI_CHIP_SEL_SW,
        .bit_rate_hz = 200000,//300000,
        .bus_role = IF_BUS_ROLE_MASTER,
        .tx_mode = SPI_TX_FULL_DUPLEX,
        .interrupt_on = true,
        .name = "SD-CARD",
        .move_mode = MOVE_MODE_INTERRUPT,
        .frame_size = 8,
        .irq_priority = 2,
        .PadSck = { .port = PORT_B, .pin = 10, },
        .PadMosi = { .port = PORT_B, .pin = 15, },
        .PadMiso = { .port = PORT_B, .pin = 14, },
        .phase = SPI_CLK_IDLE_LEVEL_0,
        .valid = true,
    },
#endif
};

SpiHandle_t SpiInstance[] = {
#ifdef HAS_SPI1
    {.num = 1, .valid = true,},
#endif

#ifdef HAS_SPI2
    {.num = 2, .valid = true,},
#endif
};

COMPONENT_GET_CNT(Spi, spi)
