#ifndef DMA_CHANNEL_I2S2_CONFIG_H
#define DMA_CHANNEL_I2S2_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

#define I2S_DMA_MEMCPY_SIZE 128

bool CallBackDoneI2s2Rx(void);
bool CallBackDoneI2s2Tx(void);
bool CallBackHalfI2s2Rx(void);
bool CallBackHalfI2s2Tx(void);
bool CallBackErrorI2s2Rx(void);
bool CallBackErrorI2s2Tx(void);


#define DMA_CHANNEL_I2S_COMMON                      \
 .memory_burst = DMA_BURST_SINGLE,                  \
 .periph_burst = DMA_BURST_SINGLE,                  \
        .aligment_per = DMA_ALIGNMENT_WORD,         \
        .aligment_mem = DMA_ALIGNMENT_WORD,         \
        .interrupt_on = true,                       \
        .block_count =1,                            \
        .valid = true,                              \
        .mode = DMA_MODE_CIRCULAR,                  \
        .fifo = DMA_FIFO_OFF,                       \
        .priority = DMA_PRIOR_VERY_HIGH,


#define DMA_CHANNEL_I2S2_RX                         \
    {                                               \
        DMA_CHANNEL_I2S_COMMON                      \
        .per_inc = DMA_INC_OFF,                     \
        .mem_inc = DMA_INC_ON,                      \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,       \
        .name = "I2s2rx",                           \
        .num = DMA_CHANNEL_NUM_I2S2_RX,             \
        .base_addr_source = (uint32_t) fromArray,   \
        .DmaChPad = { .dma_num = 1, .channel = 3, .stream=3,  .name = "I2s2rx", },      \
        .base_addr_destination =(uint32_t) &(I2S2ext->DR), \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,   \
        .CallBackHalf= CallBackHalfI2s2Rx,          \
        .CallBackDone= CallBackDoneI2s2Rx,          \
    },


#define DMA_CHANNEL_I2S2_TX                    \
    {                                          \
 .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,         \
 .DmaChPad = { .dma_num = 1, .channel = 0, .stream=4,  .name = "I2S2_TX", },      \
 .name = "I2s2Tx",                             \
 .mem_inc = DMA_INC_ON,                        \
 .per_inc = DMA_INC_OFF,                       \
  DMA_CHANNEL_I2S_COMMON                       \
 .num = DMA_CHANNEL_NUM_I2S2_TX,               \
 .CallBackHalf= CallBackHalfI2s2Tx,            \
 .CallBackDone= CallBackDoneI2s2Tx,            \
 .base_addr_source = (uint32_t)&(SPI2->DR),    \
 .base_addr_destination =(uint32_t) toArray,   \
    },

#define DMA_CHANNEL_I2S2 \
    DMA_CHANNEL_I2S2_TX  \
    DMA_CHANNEL_I2S2_RX



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_I2S2_CONFIG_H  */
