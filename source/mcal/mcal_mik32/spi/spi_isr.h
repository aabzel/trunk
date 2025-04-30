#ifndef SPI_ISR_H
#define SPI_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "spi_drv.h"
#include "spi_custom_types.h"
#include "mik32_hal.h"
#include "sys_config.h"

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

#ifndef HAS_SPI_ISR
#error "+HAS_SPI_ISR"
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPI_ISR_H  */
