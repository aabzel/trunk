#ifndef DMA_CHANNEL_UART_CONFIG_H
#define DMA_CHANNEL_UART_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef HAS_UART1
#include "dma_channel_config_uart1.h"
#else
#define DMA_CHANNEL_UART1
#endif

#define DMA_CHANNEL_UART  \
    DMA_CHANNEL_UART1

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_UART_CONFIG_H  */
