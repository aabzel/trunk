#ifndef DMA_CHANNEL_CONFIG_H
#define DMA_CHANNEL_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

typedef enum{
   //DMA_CHANNEL_NUM_UNDEF = 0,

   DMA_CHANNEL_NUM_MEMCPY1 ,
   DMA_CHANNEL_NUM_MEMCPY2 ,

#ifdef HAS_ADC1
   DMA_CHANNEL_NUM_ADC1 ,
#endif

#ifdef HAS_ADC2
   DMA_CHANNEL_NUM_ADC2 ,
#endif

#ifdef HAS_ADC3
   DMA_CHANNEL_NUM_ADC3,
#endif

#ifdef HAS_SPI1
   DMA_CHANNEL_NUM_SPI1_TX ,
   DMA_CHANNEL_NUM_SPI1_RX ,
#endif

#ifdef HAS_SPI2
   DMA_CHANNEL_NUM_SPI2_TX ,
   DMA_CHANNEL_NUM_SPI2_RX ,
#endif

#ifdef HAS_I2S2
   DMA_CHANNEL_NUM_I2S2_TX ,
   DMA_CHANNEL_NUM_I2S2_RX ,
#endif

#ifdef HAS_SPI3
   DMA_CHANNEL_NUM_SPI3_TX ,
   DMA_CHANNEL_NUM_SPI3_RX ,
#endif

#ifdef HAS_UART1
   DMA_CHANNEL_NUM_UART1_TX ,
   DMA_CHANNEL_NUM_UART1_RX ,
#endif

#ifdef HAS_SDIO
   DMA_CHANNEL_NUM_SDIO_RX ,
   DMA_CHANNEL_NUM_SDIO_TX ,
#endif

   DMA_CHANNEL_NUM_CNT
}DmaChannelLegalNums_t;

extern const DmaChannelConfig_t DmaChannelConfig[];
extern volatile DmaChannelHandle_t DmaChannelInstance[];

uint32_t dma_channel_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_H  */
