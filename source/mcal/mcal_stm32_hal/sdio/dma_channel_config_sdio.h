#ifndef DMA_CHANNEL_SDIO_CONFIG_H
#define DMA_CHANNEL_SDIO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"
#include "dma_channel_config.h"

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

bool CallBackDoneSdio1Rx(void);
bool CallBackDoneSdio1Tx(void);
bool CallBackHalfSdio1Rx(void);
bool CallBackHalfSdio1Tx(void);
bool CallBackErrorSdio1Rx(void);
bool CallBackErrorSdio1Tx(void);

#define DMA_SDIO_MEMCPY_SIZE 50
extern  uint8_t SdiotoArray[DMA_SDIO_MEMCPY_SIZE];
extern  uint8_t SdiofromArray[DMA_SDIO_MEMCPY_SIZE];

/*DMA_PFCTRL DMA_PFCTRL DMA_PFCTRL DMA_PFCTRL*/
#define DMA_CHANNEL_SDIO_COMMON                      \
        .mode = DMA_MODE_PFCTRL,                     \
        .block_size = (uint32_t) MIN( sizeof(SdiotoArray) ,sizeof(SdiofromArray))  ,    \
        .per_inc = DMA_INC_OFF,                      \
        .mem_inc = DMA_INC_ON,                       \
        .aligment_mem = DMA_ALIGNMENT_DWORD,         \
        .aligment_per = DMA_ALIGNMENT_DWORD,         \
        .memory_burst = DMA_BURST_INC4,              \
        .periph_burst = DMA_BURST_INC4,              \
        .fifo = DMA_FIFO_ON,                         \
        .priority = DMA_PRIOR_VERY_HIGH,             \
        .valid = true,                               \
        .interrupt_on = true,

#define DMA_CHANNEL_SDIO_RX                          \
    {                                                \
        .DmaChPad = { .dma_num = 2, .stream = 3, .channel = 4, .name = "SDIO1_RX",  },      \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,        \
        DMA_CHANNEL_SDIO_COMMON                      \
        .name = "SDIO1_RX",                          \
        .num = DMA_CHANNEL_NUM_SDIO_RX,              \
        .CallBackHalf = CallBackHalfSdio1Rx,         \
        .CallBackDone = CallBackDoneSdio1Rx,         \
        .base_addr_source = (uint32_t) SdiofromArray,    \
        .base_addr_destination = (uint32_t) SdiotoArray, \
        .block_count = 1,                            \
        .mux = 0,                                    \
    },

#define DMA_CHANNEL_SDIO_TX                         \
    {                                               \
        .DmaChPad = { .dma_num = 2,  .stream = 6,  .channel = 4, .name = "SDIO_TX",},      \
        .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,       \
         DMA_CHANNEL_SDIO_COMMON                    \
        .num = DMA_CHANNEL_NUM_SDIO_TX,             \
        .name = "SDIO_TX",                         \
        .CallBackHalf = CallBackHalfSdio1Tx,        \
        .CallBackDone = CallBackDoneSdio1Tx,        \
        .base_addr_source = (uint32_t)SdiofromArray,    \
        .base_addr_destination =(uint32_t) SdiotoArray, \
        .block_count = 1,                           \
        .mux = 0,                                   \
    },

#define DMA_CHANNEL_SDIO \
    DMA_CHANNEL_SDIO_TX  \
    DMA_CHANNEL_SDIO_RX



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_SDIO_CONFIG_H  */
