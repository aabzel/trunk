#ifndef DMA_CHANNEL_GPIO_CONFIG_H
#define DMA_CHANNEL_GPIO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_channel_config_gpioa.h"

#ifdef HAS_DMA_PORT_B
#include "dma_channel_config_gpiob.h"
#else
#define DMA_CHANNEL_PORT_B
#endif

#ifdef HAS_DMA_PORT_C
#include "dma_channel_config_gpioc.h"
#else
#define DMA_CHANNEL_PORT_C
#endif

#define DMA_CHANNEL_GPIO   \
    DMA_CHANNEL_PORT_A     \
    DMA_CHANNEL_PORT_B     \
    DMA_CHANNEL_PORT_C



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_GPIO_CONFIG_H  */
