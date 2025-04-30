#ifndef SPI_STM_CONST_H
#define SPI_STM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_dep.h"

#define SPI_TX_DONE_TIME_OUT_MS 300
#define SPI_RX_DONE_TIME_OUT_MS 300

typedef enum  {
    SPI0_INX = 0,
    SPI1_INX = 1,
    SPI2_INX = 2,
    SPI3_INX = 3,
    SPI4_INX = 4,
    SPI5_INX = 5,
    SPI_UNDEF_INX = 0,
    //SPI_CNT = 6
} SpiName_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_STM_CONST_H  */
