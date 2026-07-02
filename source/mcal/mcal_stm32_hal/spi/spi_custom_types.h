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

/*28.5.3 SPI status register (SPI_SR)*/
typedef union {
    uint32_t dword;
    struct {
        uint32_t RXNE :1; // Bit 0 RXNE: Receive buffer not empty
        uint32_t TXE :1; // Bit 1 TXE: Transmit buffer empty
        uint32_t CHSIDE :1; // Bit 2 CHSIDE: Channel side
        uint32_t UDR :1; // Bit 3 UDR: Underrun flag
        uint32_t CRCERR :1; // Bit 4 CRCERR: CRC error flag
        uint32_t MODF :1; // Bit 5 MODF: Mode fault
        uint32_t OVR :1; // Bit 6 OVR: Overrun flag
        uint32_t BSY :1; // Bit 7 BSY: Busy flag
        uint32_t FRE :1; // Bit 8 FRE: Frame format error (  I2S)
        uint32_t RES:23; //   9-31:
    };
} SpiStm32RegStatus_t;

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
