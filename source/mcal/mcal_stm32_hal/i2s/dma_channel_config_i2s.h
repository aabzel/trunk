#ifndef DMA_CHANNEL_I2S_CONFIG_H
#define DMA_CHANNEL_I2S_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_I2S1
#include "dma_channel_config_i2s1.h"
#else
#define DMA_CHANNEL_I2S1
#endif

#ifdef HAS_I2S2
#include "dma_channel_config_i2s2.h"
#else
#define DMA_CHANNEL_I2S2
#endif

#ifdef HAS_I2S3
#include "dma_channel_config_i2s3.h"
#else
#define DMA_CHANNEL_I2S3
#endif

#define DMA_CHANNEL_I2S  \
    DMA_CHANNEL_I2S1     \
    DMA_CHANNEL_I2S2     \
    DMA_CHANNEL_I2S3



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_I2S_CONFIG_H  */
