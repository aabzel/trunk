#ifndef DMA_CHANNEL_UART1_CONFIG_H
#define DMA_CHANNEL_UART1_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

bool CallBackDoneUart1Rx(void);
bool CallBackDoneUart1Tx(void);

bool CallBackHalfUart1Rx(void);
bool CallBackHalfUart1Tx(void);

#define DMA_CHANNEL_UART_COMMON_CONFIGS             \
        .valid = true,                              \
        .aligment_per = DMA_ALIGNMENT_BYTE,         \
        .aligment_mem = DMA_ALIGNMENT_BYTE,         \
        .block_count = 1,                           \
        .mode = DMA_MODE_NORMAL,                    \
        .interrupt_on = true,                       \
        .mem_inc = DMA_INC_ON,                      \
        .per_inc = DMA_INC_OFF,                     \
        .memory_burst = DMA_BURST_SINGLE,           \
        .periph_burst = DMA_BURST_SINGLE,           \
        .fifo = DMA_FIFO_OFF,                       \
        .priority = 10,

#ifdef HAS_UART1_DMA_RX
#define DMA_CHANNEL_UART1_RX                                   \
    {                                                          \
        DMA_CHANNEL_UART_COMMON_CONFIGS                        \
        .DmaChPad={.dma_num = 2, .stream = 2, .channel = 4,},  \
        .num = DMA_CHANNEL_NUM_UART1_RX,                       \
        .name = "USART1_RX",                                   \
        .base_addr_source = (uint32_t) &(USART1->DR),          \
        .base_addr_destination =(uint32_t) NULL,               \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,              \
        .CallBackHalf= CallBackHalfUart1Rx,                    \
        .CallBackDone= CallBackDoneUart1Rx,                    \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,                  \
    },
#else
#define DMA_CHANNEL_UART1_RX
#endif

#define DMA_CHANNEL_UART1_TX                                       \
    {                                                              \
        DMA_CHANNEL_UART_COMMON_CONFIGS                            \
        .DmaChPad = { .dma_num = 2,  .stream = 7, .channel = 4,},  \
        .name = "USART1_TX",                                       \
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,                      \
        .num = DMA_CHANNEL_NUM_UART1_TX,                           \
        .CallBackHalf= CallBackHalfUart1Tx,                        \
        .CallBackDone= CallBackDoneUart1Tx,                        \
        .base_addr_source = (uint32_t)NULL,                        \
        .base_addr_destination =(uint32_t) &(USART1->DR),          \
    },

#define DMA_CHANNEL_UART1 \
    DMA_CHANNEL_UART1_RX  \
    DMA_CHANNEL_UART1_TX

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_UART1_CONFIG_H  */
