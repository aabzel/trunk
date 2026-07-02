#ifndef DMA_CHANNEL_SPI_CONFIG_H
#define DMA_CHANNEL_SPI_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_SPI1
#include "dma_channel_config_spi1.h"
#else
#define DMA_CHANNEL_SPI1
#endif

#ifdef HAS_SPI2
#include "dma_channel_config_spi2.h"
#else
#define DMA_CHANNEL_SPI2
#endif

#ifdef HAS_SPI3
#include "dma_channel_config_spi3.h"
#else
#define DMA_CHANNEL_SPI3
#endif

#define DMA_CHANNEL_SPI  \
    DMA_CHANNEL_SPI1     \
    DMA_CHANNEL_SPI2     \
    DMA_CHANNEL_SPI3



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_SPI_CONFIG_H  */
