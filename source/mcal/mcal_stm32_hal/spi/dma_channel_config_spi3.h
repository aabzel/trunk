#ifndef DMA_CHANNEL_SPI3_CONFIG_H
#define DMA_CHANNEL_SPI3_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

bool CallBackDoneSpi3Rx(void);
bool CallBackDoneSpi3Tx(void);

bool CallBackHalfSpi3Rx(void);
bool CallBackHalfSpi3Tx(void);

bool CallBackErrorSpi3Rx(void);
bool CallBackErrorSpi3Tx(void);

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
        .mux = 0,                                       \
        .block_count = 1,                               \
        .fifo = DMA_FIFO_OFF,

#define DMA_CHANNEL_SPI3_TX                                      \
    {                                                            \
        .base_addr_destination = (uint32_t) toArray,             \
        DMA_CHANNEL_SPI_COMMON_CONFIG                            \
        .name = "Spi3Tx",                                        \
        .DmaChPad = {.dma_num = 1,  .stream = 5, .channel=0, },  \
        .num = DMA_CHANNEL_NUM_SPI3_TX,                          \
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,                    \
        .CallBackHalf = CallBackHalfSpi3Tx,                      \
        .CallBackDone = CallBackDoneSpi3Tx,                      \
        .mem_inc = DMA_INC_ON,                                   \
        .base_addr_source = (uint32_t)&(SPI3->DR),               \
        .per_inc = DMA_INC_OFF,                                  \
    },

#define DMA_CHANNEL_SPI3_RX                                     \
    {                                                           \
        .base_addr_destination = (uint32_t) &(SPI3->DR),        \
        DMA_CHANNEL_SPI_COMMON_CONFIG                           \
        .DmaChPad = {.dma_num = 1, .stream = 0, .channel = 0},  \
        .name = "Spi3rx",                                       \
        .num = DMA_CHANNEL_NUM_SPI3_RX,                         \
        .base_addr_source = (uint32_t) fromArray,               \
        .CallBackHalf = CallBackHalfSpi3Rx,                     \
        .CallBackDone = CallBackDoneSpi3Rx,                     \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,                   \
        .mem_inc = DMA_INC_ON,                                  \
        .per_inc = DMA_INC_OFF,                                 \
    },

#define DMA_CHANNEL_SPI3   \
    DMA_CHANNEL_SPI3_TX    \
    DMA_CHANNEL_SPI3_RX


#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_SPI3_CONFIG_H  */
