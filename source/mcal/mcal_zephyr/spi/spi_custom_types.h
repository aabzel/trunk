#ifndef SPI_ZEPHYR_TYPES_H
#define SPI_ZEPHYR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "spi_config.h"
#include "spi_custom_const.h"

#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/kernel.h>

#ifndef HAS_ZEPHYR
#error "+HAS_ZEPHYR"
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif

typedef struct {
    uint8_t num;
    struct device* SpiDev;
} SpiInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* SPI_ZEPHYR_TYPES_H  */
