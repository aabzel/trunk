#ifndef SPI_CUSTOM_TYPES_H
#define SPI_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_custom_const.h"
#include "microcontroller_types.h"
#include "clock_const.h"


//13.4.1 SPI control register1 (SPI_CTRL1) (Not used in I2S mode)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t CLKPHA :1;   /* Bit 0   Clock phase*/
        volatile uint32_t CLKPOL :1;   /* Bit 1   Clock polarity*/
        volatile uint32_t MSTEN :1;   /* Bit 2  Master enable*/
        volatile uint32_t MDIV :3;   /* Bit 5: 3   Master clock frequency division*/
        volatile uint32_t SPIEN :1;   /* Bit 6   SPI enable*/
        volatile uint32_t LTF :1;   /* Bit 7   LSB transmit first*/
        volatile uint32_t SWCSIL :1;   /* Bit 8   Software CS internal level*/
        volatile uint32_t SWCSEN :1;   /* Bit 9   Software CS enable*/
        volatile uint32_t ORA :1;   /* Bit 10   Receive-only active*/
        volatile uint32_t FBN :1;   /*  Bit 11  Frame bit num*/
        volatile uint32_t NTC :1;   /*Bit 12    Transmit CRC next*/
        volatile uint32_t CCEN :1;   /* Bit 13   RC calculation enable*/
        volatile uint32_t SLBTD :1;   /* Bit 14   Single line bidirectional half-duplex transmission direction
This bit and the SLBEN bit together determine the data
output direction in “Single line bidirectional half-duplex”
mode.*/
        volatile uint32_t SLBEN :1;   /* Bit 15   Single line bidirectional half-duplex enable*/
        volatile uint32_t RESERVED :16;   /* Bit 31-16   xxxxxxx*/
    };

}SpiRegCtrl1_t;

#define SPI_CUSTOM_VARIABLES   \
    spi_type* SPIx;


typedef struct {
    bool valid;
    spi_type *SPIx;
    uint8_t num;
    ClockBus_t clock_bus;
    crm_periph_clock_type clock_type;
    IRQn_Type irq_n;
}SpiInfo_t;

typedef struct {
    bool valid;
    spi_mclk_freq_div_type  code;
    uint16_t divider;
}SpiDivider_t;

typedef struct {
    spi_mclk_freq_div_type code;
    int32_t prescaler_diff_abs;
    uint16_t divider;
}SpiDividerItem_t;



#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_TYPES_H  */
