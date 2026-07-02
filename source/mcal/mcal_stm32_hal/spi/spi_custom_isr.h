#ifndef SPI_CUSTOM_ISR_H
#define SPI_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "spi_custom_types.h"
#include "stm32fx_hal.h"
#include "sys_config.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

#ifndef HAS_SPI_INTERRUPT
#error "+HAS_SPI_INTERRUPT"
#endif

bool SPIx_IRQHandler(const uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_ISR_H  */
