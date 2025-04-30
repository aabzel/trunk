#ifndef I2S_STM32_TYPES_H
#define I2S_STM32_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "i2s_custom_const.h"

/*SPI_I2S configuration register*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t chlen  :1;  /*Channel length (number of bits per audio channel)*/
        uint32_t datlen :2;  /*Data length to be transferred*/
        uint32_t ckpol  :1;  /*Steady state clock polarity*/
        uint32_t i2sstd :2;  /*I2S standard selection*/
        uint32_t res1    :1; /**/
        uint32_t pcmsync:1;  /*PCM frame synchronization*/
        uint32_t i2scfg :2;  /*I2S configuration mode*/
        uint32_t i2se   :1;  /*I2S Enable*/
        uint32_t i2smod :1;  /*I2S mode selection*/
        uint32_t astren :1;  /*Asynchronous start enable.*/
        uint32_t res2   :19; /**/
    };
}RegI2sConfig_t;


/*SPI_I2S prescaler register (SPI_I2SPR)*/
typedef union {
    uint32_t reg_val;
    struct{
        uint32_t i2sdiv  :8;  /*I2S Linear prescaler*/
        uint32_t odd :1;  /*Odd factor for the prescaler*/
        uint32_t mckoe  :1;  /*Master clock output enable*/
        uint32_t res :22;  /*Reserved,*/
    };
}RegI2sPsc_t;


#ifdef __cplusplus
}
#endif

#endif /* I2S_STM32_TYPES_H */
