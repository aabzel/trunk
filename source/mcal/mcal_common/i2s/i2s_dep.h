#ifndef I2S_DEP_H
#define I2S_DEP_H

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif /*HAS_GPIO*/

#ifndef HAS_I2S
#error "+ HAS_I2S"
#endif

#ifndef HAS_DFT
#warning "+ HAS_DFT"
#endif

#ifndef HAS_DDS
#warning "+ HAS_DDS"
#endif

#ifndef HAS_SPI
/*SPI needed for I2S in Artery and STM32 MCUs*/
#warning "+ HAS_SPI"
#endif

#ifndef HAS_TIME
#error "+ HAS_TIME"
#endif


#endif /* I2S_DEP_H */
