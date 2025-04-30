#ifndef SPI_STM_TYPES_H
#define SPI_STM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_custom_const.h"
#include "stm32f407xx.h"

#define SPI_CUSTOM_VARIABLES       \
    SPI_HandleTypeDef handle;      \
    SPI_TypeDef * SPIx;


typedef struct{
    uint8_t num;
    SPI_TypeDef * SPIx;
    bool valid;
}SpiInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* SPI_STM_TYPES_H  */
