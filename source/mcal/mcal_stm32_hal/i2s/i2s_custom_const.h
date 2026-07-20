#ifndef I2S_STM32_CONST_H
#define I2S_STM32_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

/*
Bits 2:1 DATLEN: Data length to be transferred
Note: For correct operation, these bits should be configured when the I2S is disabled.
This bit is not used in SPI mode.
*/
typedef enum {
   I2S_DAT_LEN16_BIT = 0,//00: 16-bit data length
   I2S_DAT_LEN24_BIT = 1,//01: 24-bit data length
   I2S_DAT_LEN32_BIT = 2,//10: 32-bit data length
   I2S_DAT_NOT_ALLOWED = 3,//11: Not allowed
}Stm32I2sDatLen_t;

//Bits 9:8 I2SCFG: I2S configuration mode
typedef enum {
    I2S_ROLE_SLAVE_TRANSMIT  = 0,  /*00: Slave - transmit*/
    I2S_ROLE_SLAVE_RECEIVE   = 1,  /*01: Slave - receive*/
    I2S_ROLE_MASTER_TRANSMIT = 2,  /*10: Master - transmit*/
    I2S_ROLE_MASTER_RECEIVE  = 3,  /*11: Master - receive*/
}Stm32I2sCnfgMode_t;

typedef enum {
   I2S_STD_I2S_PHILIPS = 0,
   I2S_STD_MSB_JUSTIFIED = 1,
   I2S_STD_LSB_JUSTIFIED = 2,
   I2S_STD_PCM =3,
}Stm32I2sStd_t;

//Bit 0 CHLEN: Channel length (number of bits per audio channel)
typedef enum {
    I2S_I2SCFGR_CHLEN_16_BIT = 0, // 0: 16-bit wide
    I2S_I2SCFGR_CHLEN_32_BIT = 1, // 1: 32-bit wide
    I2S_I2SCFGR_CHLEN_UNDEF = 2
}I2S_I2SCFGR_CHLEN_t;


/*
Bit 3 CKPOL: Steady state clock polarity
Note: For correct operation, this bit should be configured when the I2S is disabled.
This bit is not used in SPI mode
*/
typedef enum {
    I2S_CLKPOL_LOW = 0,    /* 0: I2S clock steady state is low level*/
    I2S_CLKPOL_HIGH = 1,   /* 1: I2S clock steady state is high level*/
    I2S_CLKPOL_UNDEF = 2, /**/
}I2sClockPolatity_t;

/*Bit 11 I2SMOD: I2S mode selection
0: SPI mode is selected
1: I2S mode is selected
Note: This bit should be configured when the SPI or I2S is disabled
*/
typedef enum {
    I2S_MODE_SPI = 0,
    I2S_MODE_I2S = 1,
}Stm32I2sMode_t;//13.4.8 SPI_I2S register (SPI_I2SCTRL)


//Channel length (number of bits per audio channel)
typedef enum {
    I2S_CHLEN_16=0,
    I2S_CHLEN_32=1,
}Stm32I2sChLen_t;

// Bit 9 MCKOE: Master clock output enable
typedef enum {
    SPI_I2SPR_MCKOE_DISABLED = 0,  // 0: Master clock output is disabled
    SPI_I2SPR_MCKOE_ENABLED = 1,   // 1: Master clock output is enabled
    SPI_I2SPR_MCKOE_UNDEF = 2,
}SPI_I2SPR_MCKOE_t;

// Bit 10 I2SE: I2S Enable
typedef enum {
    I2S_PERIPHERAL_IS_DISABLED = 0, // 0: I2S peripheral is disabled
    I2S_PERIPHERAL_IS_ENABLED = 1,  // 1: I2S peripheral is enabled
} I2sEnable_t;

/*
Bit 7 PCMSYNC: PCM frame synchronization
0: Short frame synchronization
1: Long frame synchronization
Note: This bit has a meaning only if I2SSTD = 11 (PCM standard is used)
It is not used in SPI mode.
 * */
typedef enum {
    I2S_PCM_FRAME_SYNC_SHORT= 0,    /* 0: Short frame synchronization*/
    I2S_PCM_FRAME_SYNC_LONG = 1,   /*1: Long frame synchronization*/
    I2S_PCM_FRAME_SYNC_UNDEF = 2, /**/
}I2sPcmFrameSynchronization_t;



#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_CONST_H */
