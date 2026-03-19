#ifndef SPI_CUSTOM_TYPES_H
#define SPI_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_custom_const.h"
#include "spi_const.h"
#include "clock_const.h"
#include "microcontroller_types.h"
#include "mcal_types.h"

#define SPI_CUSTOM_VARIABLES       \
    SPI_HandleTypeDef handle;      \
    SPI_TypeDef * SPIx;

typedef struct{
    uint8_t num;
    SPI_TypeDef* SPIx;
    ClockBus_t clock_bus;
    IRQn_Type irq_n;
    bool valid;
}SpiInfo_t;

typedef struct {
    SpiPolarity_t polarity;
    SpiClkIdleLevel_t phase;
    uint32_t clk_polarity;  // SPI_POLARITY_LOW    SPI_POLARITY_HIGH
    uint32_t clk_phase;     // SPI_PHASE_1EDGE     SPI_PHASE_2EDGE
    bool valid;
}SpiClockTimingInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_TYPES_H  */
