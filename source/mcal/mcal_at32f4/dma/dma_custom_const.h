#ifndef DMA_CUSTOM_CONST_H
#define DMA_CUSTOM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_dep.h"

typedef enum{
    DMA_MUX_UNDEF = 0,

    DMA_MUX_SPI2_RX = 12,
    DMA_MUX_SPI2_TX = 13,
    DMA_MUX_I2S2_EXT_RX = 110,
    DMA_MUX_I2S2_EXT_TX = 111,
    DMA_MUX_SPI2 = 102,
}DmaMuxNum_t;

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_CONST_H  */
