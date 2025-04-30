#ifndef I2S_CELL_TYPES_H
#define I2S_CELL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2s_register_const.h"

typedef union{
    uint16_t division;
    struct{
        uint16_t division_7_0 :8;
        uint16_t division_11_10 :2;
        uint16_t reserv :6;
    };
}I2sDiv_t;


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

}SpiCtrl1_t;


//13.4.2 SPI control register2 (SPI_CTRL2)
typedef union {
    volatile  uint32_t qword;
    struct {
        volatile uint32_t DMAREN :1;   /*Bit 0  DMA receive enable*/
        volatile uint32_t DMATEN :1;   /*Bit 1  DMA transmit enable*/
        volatile uint32_t HWCSOE :1;   /*Bit 2  Hardware CS output enable*/
        volatile uint32_t RESERVED1 :1;   /*Bit 3 ccccccc*/
        volatile uint32_t TIEN :1;   /*Bit 4 TI mode enable*/
        volatile uint32_t ERRIE :1;   /*Bit 5 Error interrupt enable*/
        volatile uint32_t RDBFIE :1;   /*Bit 6 Receive data buffer full interrupt enable*/
        volatile uint32_t TDBEIE :1;   /*Bit 7 Transmit data buffer empty interrupt enable*/
        volatile uint32_t MDIV :1;   /*Bit 8 Master clock frequency division*/
        volatile uint32_t MDIV3EN :1;   /*Bit 9 Master clock frequency divided by 3 enable*/
        volatile uint32_t RESERVED2 :22;   /*Bit 31: 10  */
    };
}SpiCtrl2_t ;

//13.4.3 SPI status register (SPI_STS)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t RDBF :1;       /* Bit 0  Receive data buffer full*/
        volatile uint32_t TDBE :1;       /* Bit 1  Transmit data buffer empty*/
        volatile uint32_t ACS :1;        /* Bit 2  Audio channel state*/
        volatile uint32_t TUERR :1;      /* Bit 3  Transmitter underload error*/
        volatile uint32_t CCERR :1;      /* Bit 4  CRC error*/
        volatile uint32_t MMERR :1;      /* Bit 5  Master mode error*/
        volatile uint32_t ROERR :1;      /* Bit 6  Receiver overflow error*/
        volatile uint32_t BF :1;         /* Bit 7  Busy flag*/
        volatile uint32_t CSPAS :1;      /* Bit 8  CS pulse abnormal setting flag*/
        volatile uint32_t RESERVED :23;  /* Bit 31: 9   */
    };
}SpiStatus_t ;

//13.4.4 SPI data register (SPI_DT)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t DT :16;   /*Bit 15: 0 Data value*/
        volatile uint32_t RESERVED :16;   /*Bit 31: 16  */
    };
}SpiData_t ;

//13.4.5 SPICRC register (SPI_CPOLY) (Not used in I2S mode)
typedef union {
    volatile uint32_t qword;
}SpiCpoly_t;

typedef union {
    volatile uint32_t qword;
}SpiCrc_t ;

//13.4.6 SPIRxCRC register (SPI_RCRC) (Not used in I2S mode)
typedef union {
    volatile uint32_t qword;
}SpiRxCrc_t ;

//13.4.7 SPITxCRC register (SPI_TCRC)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t TCRC :16;   /*Bit 15: 0 Transmit CRC*/
        volatile uint32_t RESERVED :16;   /*Bit 31: */
    };
}SpiTxCrc_t ;

//13.4.8 SPI_I2S register (SPI_I2SCTRL)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t I2SCBN :1;   /*Bit 0 I2S channel bit num*/
        volatile uint32_t I2SDBN :2;   /*Bit 2: 1  I2S data bit num*/
        volatile uint32_t I2SCLKPOL :1;   /*Bit 3  I2S clock polarity*/
        volatile uint32_t STDSEL :2;   /*Bit 5: 4 I2S standard select*/
        volatile uint32_t RESERVED1 :1;   /*Bit 6*/
        volatile uint32_t PCMFSSEL :1;   /*Bit 7 PCM frame synchronization*/
        volatile uint32_t OPERSEL :2;   /*Bit 9: 8 I2S operation mode select*/
        volatile uint32_t I2SEN :1;   /*Bit 10 I2S enable*/
        volatile uint32_t I2SMSEL :1;   /*Bit 11 I2S mode select*/
        volatile uint32_t RESERVED2 :20;   /*Bit 31: 12 */
    };
}SpiI2sCtrl_t ;

//13.4.9 SPI_I2S prescaler register (SPI_I2SCLKP)
typedef union {
    volatile uint32_t qword;
    struct {
        volatile uint32_t I2SDIV1 :8;   /*Bit 7:0 I2S division */
        volatile uint32_t I2SODD :1;   /*Bit 8  Odd factor for I2S division */
        volatile uint32_t I2SMCLKOE :1;   /*Bit 9 I2S Master clock output enable*/
        volatile uint32_t I2SDIV2 :2;   /*Bit 11: 10 I2S division */
        volatile uint32_t RESERVED :20;   /*Bit 31: 12 Reserved*/
    };
}SpiI2sClkPrescaler_t;


#ifdef __cplusplus
}
#endif

#endif /* I2S_CELL_TYPES_H */
