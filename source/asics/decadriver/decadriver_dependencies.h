#ifndef DECADRIVER_DEPENDENCIES_H
#define DECADRIVER_DEPENDENCIES_H

#ifndef HAS_DECADRIVER
#error "+HAS_DECADRIVER"
#endif

#ifndef HAS_MCU
#error "+HAS_MCU"
#endif

#ifndef HAS_DW1000
#error "+HAS_DW1000"
#endif

#ifndef HAS_DWM1000
#error "+HAS_DWM1000"
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

#ifndef HAS_DECADRIVER_TX
#warning "+HAS_DECADRIVER_TX"
#endif

#endif /* DECADRIVER_DEPENDENCIES_H  */
