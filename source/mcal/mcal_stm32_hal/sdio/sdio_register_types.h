#ifndef SDIO_REGISTER_TYPES_H
#define SDIO_REGISTER_TYPES_H


#include <stdint.h>

/*
  SDIO Status Register (SDIO_STA) bit fields
 */
typedef union {
    volatile uint32_t dword;  /* Full register access */
    struct {
        volatile uint32_t CCRCFAIL : 1;  /* Bit 0 CCRCFAIL: Command response received (CRC check failed) */
        volatile uint32_t DCRCFAIL : 1;  /* Bit 1 DCRCFAIL: Data block sent/received (CRC check failed) */
        volatile uint32_t CTIMEOUT : 1;  /* Bit 2 CTIMEOUT: Command response timeout */
        volatile uint32_t DTIMEOUT : 1;  /* Bit 3 DTIMEOUT: Data timeout */
        volatile uint32_t TXUNDERR : 1;  /* Bit 4 TXUNDERR: Transmit FIFO underrun error */
        volatile uint32_t RXOVERR : 1;   /* Bit 5 RXOVERR:  Received FIFO overrun error */
        volatile uint32_t CMDREND : 1;   /* Bit 6 CMDREND:  Command response received (CRC check passed) */
        volatile uint32_t CMDSENT : 1;   /* Bit 7 CMDSENT:  Command sent (no response required) */
        volatile uint32_t DATAEND : 1;   /* Bit 8 DATAEND:  Data end (data counter, SDIDCOUNT, is zero) */
        volatile uint32_t STBITERR : 1;  /* Bit 9 STBITERR: Start bit not detected on all data signals in wide bus mode */
        volatile uint32_t DBCKEND : 1;   /* Bit 10 DBCKEND: Data block sent/received (CRC check passed) */
        volatile uint32_t CMDACT : 1;    /* Bit 11 CMDACT:  Command transfer in progress */
        volatile uint32_t TXACT : 1;     /* Bit 12 TXACT:   Data transmit in progress*/
        volatile uint32_t RXACT : 1;     /* Bit 13 RXACT:   Data receive in progress */
        volatile uint32_t TXFIFOHE : 1;  /* Bit 14 TXFIFOHE: Transmit FIFO half empty: at least 8 words can be written into the FIFO */
        volatile uint32_t RXFIFOHF : 1;  /* Bit 15 RXFIFOHF: Receive FIFO half full: there are at least 8 words in the FIFO */
        volatile uint32_t TXFIFOF : 1;   /* Bit 16 TXFIFOF: Transmit FIFO full */
        volatile uint32_t RXFIFOF : 1;   /* Bit 17 RXFIFOF: Receive FIFO full */
        volatile uint32_t TXFIFOE : 1;   /* Bit 18 TXFIFOE: Transmit FIFO empty*/
        volatile uint32_t RXFIFOE : 1;   /* Bit 19 RXFIFOE: Receive FIFO empty */
        volatile uint32_t TXDAVL : 1;    /* Bit 20 TXDAVL: Data available in transmit FIFO */
        volatile uint32_t RXDAVL : 1;    /* Bit 21 RXDAVL: Data available in receive FIFO */
        volatile uint32_t SDIOIT : 1;    /* Bit 22 SDIOIT: SDIO interrupt received */
        volatile uint32_t CEATAEND : 1;  /* Bit 23 CEATAEND: CE-ATA command completion signal received for CMD61 */
        volatile uint32_t RESERVED : 8;  /* Bits 31-24: Reserved */
    } ;                         /* Structure for accessing individual bits */
} SdioRegSDIO_STA_t;


/*
  SDIO clock control register (SDIO_CLKCR)

  Address offset: 0x04
  Reset value: 0x0000 0000
 */
typedef union {
    volatile uint32_t dword;                   /* Raw register value */
    struct {
        volatile uint32_t CLKDIV  : 8;         /* Clock divide factor, bits [7:0] */
        volatile uint32_t CLKEN   : 1;         /* Clock enable, bit 8 */
        volatile uint32_t PWRSAV  : 1;         /* Power saving mode, bit 9 */
        volatile uint32_t BYPASS  : 1;         /* Clock divider bypass, bit 10 */
        volatile uint32_t WIDBUS  : 2;         /* Bus width (1/4/8-bit), bits [12:11] */
        volatile uint32_t NEGDGE  : 1;         /* Negative edge sampling, bit 13 */
        volatile uint32_t HWFC_EN : 1;         /* Hardware flow control enable, bit 14 */
        volatile uint32_t RES: 17;       /* Reserved, bits [31:15] */
    }  ;
} SdioRegSDIO_CLKCR_t;




#endif /* SDIO_REGISTER_TYPES_H  */
