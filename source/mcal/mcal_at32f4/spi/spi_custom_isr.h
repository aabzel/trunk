#ifndef SPI_CUSTOM_ISR_H
#define SPI_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

//#include "spi_custom_types.h"
//#include "spi_mcal.h"
//#include "microcontroller_const.h"

#ifndef HAS_SPI_ISR
#error "+HAS_SPI_ISR"
#endif

bool SpiIRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_ISR_H  */
