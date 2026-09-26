#include "dma_channel_config.h"

#include "data_utils.h"

#ifdef HAS_MEMCPY_DMA
#include "dma_channel_config_memcpy.h"
#else
#define DMA_CHANNEL_MEMCPY
#endif

#ifdef HAS_ADC_DMA
#include "dma_channel_config_adc.h"
#else
#define DMA_CHANNEL_ADC
#endif

#ifdef HAS_SPI_DMA
#include "dma_channel_config_spi.h"
#else
#define DMA_CHANNEL_SPI
#endif

#ifdef HAS_I2S_DMA
#include "dma_channel_config_i2s.h"
#else
#define DMA_CHANNEL_I2S
#endif

#ifdef HAS_UART_DMA
#include "dma_channel_config_uart.h"
#else
#define DMA_CHANNEL_UART
#endif

#ifdef HAS_SDIO_DMA
#include "dma_channel_config_sdio.h"
#else
#define DMA_CHANNEL_SDIO
#endif

#ifdef HAS_GPIO_DMA
#include "dma_channel_config_gpio.h"
#else
#define DMA_CHANNEL_GPIO
#endif


#define DMA_CHANNEL_ALL  \
    DMA_CHANNEL_MEMCPY   \
    DMA_CHANNEL_ADC      \
    DMA_CHANNEL_GPIO     \
    DMA_CHANNEL_I2S      \
    DMA_CHANNEL_SDIO     \
    DMA_CHANNEL_SPI      \
    DMA_CHANNEL_UART

const DmaChannelConfig_t SECTION_CFG_DATA DmaChannelConfig[] = {
    DMA_CHANNEL_ALL
};

volatile DmaChannelHandle_t DmaChannelInstance[] = {

#ifdef HAS_GPIO_DMA
    { .num = DMA_CHANNEL_NUM_GPIOA_TX,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_GPIOA_RX,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_GPIOB,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_GPIOC,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_GPIOD,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_GPIOE,  .valid = true,    },
#endif


#ifdef HAS_ADC_DMA
    { .num = DMA_CHANNEL_NUM_ADC1,  .valid = true,    },
#endif

#ifdef HAS_I2S_DMA
    { .num = DMA_CHANNEL_NUM_I2S2_TX,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_I2S2_RX,  .valid = true,    },
#endif

#ifdef HAS_SPI_DMA
    { .num = DMA_CHANNEL_NUM_SPI3_TX,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_SPI3_RX,  .valid = true,    },
#endif

#ifdef HAS_SDIO_DMA
    { .num = DMA_CHANNEL_NUM_SDIO_RX,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_SDIO_TX,  .valid = true,    },
#endif

#ifdef HAS_MEMCPY_DMA
    { .num = DMA_CHANNEL_NUM_MEMCPY1,  .valid = true,    },
    { .num = DMA_CHANNEL_NUM_MEMCPY2,  .valid = true,    },
#endif
};

COMPONENT_GET_CNT(DmaChannel, dma_channel)
