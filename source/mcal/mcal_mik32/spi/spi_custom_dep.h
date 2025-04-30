#ifndef SPI_CUSTOM_DEP_H
#define SPI_CUSTOM_DEP_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /*HAS_MICROCONTROLLER*/

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_ISR
#error "+HAS_SPI_ISR"
#endif /*HAS_SPI_ISR*/


#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_DEP_H */
