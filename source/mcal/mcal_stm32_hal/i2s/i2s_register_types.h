#ifndef I2S_STM32_REGISTERS_TYPES_H
#define I2S_STM32_REGISTERS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/*
28.5.2   SPI control register 2 (SPI_CR2)
 */
typedef union {
    uint32_t dword;
    struct {
        uint32_t RXDMAEN : 1;  /* Bit 0 RXDMAEN: Rx buffer DMA enable                                  */
        uint32_t TXDMAEN : 1;  /* Bit 1 TXDMAEN: Tx buffer DMA enable                                  */
        uint32_t RES1    : 3;  /* Bit 2                                                                */
        uint32_t ERRIE   : 1;  /* Bit 5 ERRIE: Error interrupt enable                                  */
        uint32_t RXNEIE  : 1;  /* Bit 6 RXNEIE: RX buffer not empty interrupt enable                   */
        uint32_t TXEIE   : 1;  /* Bit 7 TXEIE: Tx buffer empty interrupt enable                        */
        uint32_t RES4    : 24; /* Bits 31:8 Reserved, must be kept at reset value.       */
    } ;
} I2sReg_SPI_CR2_t;


/*
SPI status register (SPI_SR)
 */
typedef union {
    uint32_t dword;
    struct {
        uint32_t RXNE   : 1;   /* Bit 0 RXNE: Receive buffer not empty     */
        uint32_t TXE    : 1;   /* Bit 1 TXE: Transmit buffer empty         */
        uint32_t CHSIDE : 1;   /* Bit 2 CHSIDE: Channel side               */
        uint32_t UDR   : 1;    /* Bit 3 UDR: Underrun flag                 */
        uint32_t RES1  : 2;    /* Bit 4 CRCERR: CRC error flag             */
        uint32_t OVR   : 1;    /* Bit 6 OVR: Overrun flag                  */
        uint32_t BSY   : 1;    /* Bit 7 BSY: Busy flag                     */
        uint32_t FRE   : 1;    /* Bit 8 FRE: Frame format error            */
        uint32_t RES2  : 23;   /* Bits 15:9 Reserved. Forced to 0 by hardware.    */
    } ;
} I2sReg_SPI_SR_t;

/* 28.5.4 SPI data register (SPI_DR)  */
typedef union {
    uint32_t dword;
    struct {
        uint32_t DR   : 16;   /* Bits 15:0 DR[15:0]: Data register   */
        uint32_t RES  : 16;   /* Bits 15:9 Reserved. Forced to 0 by hardware.    */
    } ;
} I2sReg_SPI_DR_t;


/*
 28.5.8 SPI_I2S configuration register (SPI_I2SCFGR)
 */
typedef union {
    uint32_t dword;
    struct{
        uint32_t CHLEN  :1;  /*Bit 0 CHLEN: Channel length (number of bits per audio channel)*/
        uint32_t DATLEN :2;  /*Bits 2:1 DATLEN: Data length to be transferred*/
        uint32_t CKPOL  :1;  /*Bit 3 CKPOL: Steady state clock polarity*/
        uint32_t I2SSTD :2;  /*Bits 5:4 I2SSTD: I2S standard selection*/
        uint32_t RES1   :1;  /*Bit 6 Reserved: forced at 0 by hardware*/
        uint32_t PCMSYNC:1;  /*Bit 7 PCMSYNC: PCM frame synchronization*/
        uint32_t I2SCFG :2;  /*Bits 9:8 I2SCFG: I2S configuration mode*/
        uint32_t I2SE   :1;  /*Bit 10 I2SE: I2S Enable*/
        uint32_t I2SMOD :1;  /*Bit 11 I2SMOD: I2S mode selection*/
        uint32_t RES2   :20; /**/
    };
}I2sReg_SPI_I2SCFGR_t;


/*
SPI_I2S prescaler register (SPI_I2SPR)
*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t I2SDIV  :8;  /*Bits 7:0 I2SDIV: I2S Linear prescaler   */
        uint32_t ODD :1;      /*Bit 8 ODD: Odd factor for the prescaler */
        uint32_t MCKOE  :1;   /*Bit 9 MCKOE: Master clock output enable*/
        uint32_t RES :22;     /*Reserved,*/
    };
}I2sReg_SPI_I2SPR_t;


#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_REGISTERS_TYPES_H */
