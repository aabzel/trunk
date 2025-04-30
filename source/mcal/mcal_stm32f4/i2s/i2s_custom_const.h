#ifndef I2S_STM32_CONST_H
#define I2S_STM32_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
   I2S_DAT_LEN16_BIT=0,
   I2S_DAT_LEN24_BIT=1,
   I2S_DAT_LEN32_BIT=2,
   I2S_DAT_NOT_ALLOWED=3,
}Stm32I2sDatLen_t;

typedef enum {
    I2S_ROLE_SLAVE_TRANSMIT =0,
    I2S_ROLE_SLAVE_RECEIVE  =1,
    I2S_ROLE_MASTER_TRANSMIT=2,
    I2S_ROLE_MASTER_RECEIVE =3,
}Stm32I2sCnfgMode_t;

typedef enum {
   I2S_STD_I2S_PHILIPS =0,
   I2S_STD_MSB_JUSTIFIED=1,
   I2S_STD_LSB_JUSTIFIED=2,
   I2S_STD_PCM =3,
}Stm32I2sStd_t;

typedef enum {
    I2S_MODE_SPI=0,
    I2S_MODE_I2S=1,
}Stm32I2sMode_t;

//Channel length (number of bits per audio channel)
typedef enum {
    I2S_CHLEN_16=0,
    I2S_CHLEN_32=1,
}Stm32I2sChLen_t;


#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_CONST_H */
