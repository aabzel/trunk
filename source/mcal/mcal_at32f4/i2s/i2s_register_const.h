#ifndef I2S_REGISTER_CONST_H
#define I2S_REGISTER_CONST_H

#include "bit_const.h"

// see 4.3.13 APB1 peripheral clock enable register (CRM_APB1EN)
//     4.3.14 APB2 peripheral clock enable register (CRM_AHB2EN)
typedef enum {
	CLOCK_PERIPH_CLOCK_I2S1 = BIT_12,
	CLOCK_PERIPH_CLOCK_I2S2 = BIT_14,
	CLOCK_PERIPH_CLOCK_I2S3 = BIT_15,
	CLOCK_PERIPH_CLOCK_I2S4 = BIT_13,

	CLOCK_PERIPH_CLOCK_UNDEF = 0,
}I2cClockMask_t;

typedef enum{
    I2S_FLAG_RDBF   = BIT_0,     /*Receive data buffer full */
    I2S_FLAG_TDBE   = BIT_1,     /*Transmit data buffer empty */
    I2S_FLAG_ACS    = BIT_2,     /*Audio channel state */
    I2S_FLAG_TUERR  = BIT_3,     /*Transmitter underload error */
    I2S_FLAG_CCERR  = BIT_4,     /*CRC error */
    I2S_FLAG_MMERR  = BIT_5,     /*Master mode error */
    I2S_FLAG_ROERR  = BIT_6,     /*Receiver overflow error */
    I2S_FLAG_BF     = BIT_7,     /*Busy flag */
    I2S_FLAG_CSPAS  = BIT_8,     /*CS pulse abnormal setting flag */

    I2S_FLAG_UNDEF   =  BIT_15,
}I2sFlag_t;

//13.4.8 SPI_I2S register (SPI_I2SCTRL)
typedef enum {
    I2SMSEL_SPI = 0,
    I2SMSEL_I2S = 1,
    I2SMSEL_UNDEF = 2,
}SpiI2sMode_t;




typedef enum{
	ACS_CHANNEL_LEFT = 0,
	ACS_CHANNEL_RIGHT = 1,
	ACS_CHANNEL_UNDEF = 2,
}I2sAudioChannel_t;


typedef enum{
    I2SEN_OFF = 0,
    I2SEN_ON = 1,
    I2SEN_UNDEF = 2,
}I2sEnable_t;

typedef enum{
    OPERSEL_SLAVE_TX = 0,
    OPERSEL_SLAVE_RX = 1,
    OPERSEL_MASTER_TX = 2,
    OPERSEL_MASTER_RX = 3,

    OPERSEL_UNDEF = 4,
}I2sOperation_t;

typedef enum{
    STDSEL_PHILIPS = 0,
    STDSEL_LEFT_ALIGNE = 1,
    STDSEL_RIGHT_ALIGNED = 2,
    STDSEL_PCM = 3,

    STDSEL_UNDEF = 4,
}I2sStandart_t;


typedef enum{
    I2SCLKPOL_LOW = 0,
    I2SCLKPOL_HIGH = 1,

    I2SCLKPOL_UNDEF = 2,
}I2sClockPolatity_t;

typedef enum{
    I2SDBN_16BIT = 0,
    I2SDBN_24BIT = 1,
    I2SDBN_32BIT = 2,
    I2SDBN_RESERV = 3,

    I2SDBN_UNDEF = 4,
}I2sBitLen_t;

typedef enum{
    I2SCBN_16BIT_WIDE = 0,
    I2SCBN_32BIT_WIDE = 1,

    I2SCBN_UNDEF = 2,
}I2sChannelBitNum_t;

typedef enum{
    I2SMCLKOE_OFF = 0,
    I2SMCLKOE_ON = 1,

    I2SMCLKOE_UNDEF = 2,
}I2sMasterClockOut_t;

typedef enum{
    I2SODD_EVEN = 0,
    I2SODD_ODD = 1,

    I2SODD_UNDEF = 2,
}I2sOddFactor_t;


typedef enum{
    I2S_INTERRUPT_ERROR=5,
    I2S_INTERRUPT_RX_FULL=6,//RDBF
    I2S_INTERRUPT_TX_EMPTY=7,//TDBE

    I2S_INTERRUPT_UNDEF=0,
}I2sInterrupt_t;

#endif /* I2S_REGISTER_CONST_H */
