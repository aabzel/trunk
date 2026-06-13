#include "spi_config.h"

#include "data_utils.h"
#include "spi_types.h"

const SpiConfig_t SpiConfig[] = {
   {.num = 1,
    .frame_size = 8,
    .interrupt_on = true,
    .bus_role = BUS_ROLE_MASTER,
    .tx_mode = SPI_TX_FULL_DUPLEX,
    //.bit_rate_hz = 250000,
    //.bit_rate_hz = 400000, //
    .bit_rate_hz = 800000, //
    .move_mode = MOVE_MODE_INTERRUPT,
    .bit_order = BIT_ORDER_MSB,
    .direction = SPI_DIRECTION_2WIRES,
    .polarity = SPI_POLARITY_LATCH_RISING,
    .phase = SPI_CLK_IDLE_LEVEL_0,
    .chip_select = SPI_CHIP_SEL_SW,
    .name = "MX25L6433F",
    .irq_priority = 0,
    .valid = true
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
    {.num=1, .valid=true},
#ifdef HAS_SPI5
    {.num=5, .valid=true},
#endif
};

COMPONENT_GET_CNT(Spi, spi)

