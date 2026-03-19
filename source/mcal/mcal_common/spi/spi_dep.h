#ifndef SPI_DEP_H
#define SPI_DEP_H

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif /**/

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /**/

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif /**/

#ifndef HAS_TIME
#error "+HAS_TIME"
#endif /**/

#ifndef HAS_INTERRUPT
#error "+HAS_INTERRUPT"
#endif

#ifndef HAS_DMA
#warning "+HAS_DMA"
#endif /**/

#ifndef HAS_DMA_CHANNEL
#warning "+HAS_DMA_CHANNEL"
#endif /**/

#endif /* SPI_DEP_H */
