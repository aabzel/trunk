#ifndef DMA_CHANNEL_SPI2_CONFIG_H
#define DMA_CHANNEL_SPI2_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

bool CallBackDoneSpi2Rx(void);
bool CallBackDoneSpi2Tx(void);

bool CallBackHalfSpi2Rx(void);
bool CallBackHalfSpi2Tx(void);

bool CallBackErrorSpi2Rx(void);
bool CallBackErrorSpi2Tx(void);

#define DMA_CHANNEL_SPI_COMMON_CONFIG                   \
        .memory_burst = DMA_BURST_SINGLE,               \
        .periph_burst = DMA_BURST_SINGLE,               \
        .priority = 10,                                 \
        .mode = DMA_MODE_NORMAL,                        \
        .aligment_per = DMA_ALIGNMENT_BYTE,             \
        .aligment_mem = DMA_ALIGNMENT_BYTE,             \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,       \
        .valid = true,                                  \
        .interrupt_on = true,                           \
        .mux = 0,                                                \
        .block_count = 1,                               \
        .fifo = DMA_FIFO_OFF,

#define DMA_CHANNEL_SPI2_TX                                      \
    {                                                            \
        .base_addr_destination = (uint32_t) toArray,             \
        DMA_CHANNEL_SPI_COMMON_CONFIG                            \
        .name = "Spi2Tx",                                        \
        .DmaChPad = {.dma_num = 1,  .stream = 4, .channel=0, },    \
        .num = DMA_CHANNEL_NUM_SPI2_TX,                          \
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,                    \
        .CallBackHalf = CallBackHalfSpi2Tx,                      \
        .CallBackDone = CallBackDoneSpi2Tx,                      \
        .mem_inc = DMA_INC_ON,                                   \
        .base_addr_source = (uint32_t)&(SPI2->DR),               \
        .per_inc = DMA_INC_OFF,                                  \
    },

#define DMA_CHANNEL_SPI2_RX                                     \
    {                                                           \
        .base_addr_destination = (uint32_t) &(SPI2->DR),        \
        DMA_CHANNEL_SPI_COMMON_CONFIG                           \
        .DmaChPad = {.dma_num = 1, .stream = 3, .channel = 0},  \
        .name = "Spi2rx",                                       \
        .num = DMA_CHANNEL_NUM_SPI2_RX,                         \
        .base_addr_source = (uint32_t) fromArray,               \
        .CallBackHalf = CallBackHalfSpi2Rx,                     \
        .CallBackDone = CallBackDoneSpi2Rx,                     \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,                   \
        .mem_inc = DMA_INC_ON,                                  \
        .per_inc = DMA_INC_OFF,                                 \
    },

#define DMA_CHANNEL_SPI2           \
    DMA_CHANNEL_SPI2_TX            \
    DMA_CHANNEL_SPI2_RX


#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_SPI2_CONFIG_H  */
