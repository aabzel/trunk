#ifndef DMA_CHANNEL_SDIO_CONFIG_H
#define DMA_CHANNEL_SDIO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"


bool CallBackDoneSdio1Rx(void);
bool CallBackDoneSdio1Tx(void);
bool CallBackHalfSdio1Rx(void);
bool CallBackHalfSdio1Tx(void);
bool CallBackErrorSdio1Rx(void);
bool CallBackErrorSdio1Tx(void);

#define DMA_CHANNEL_SDIO_RX                         \
    {                                               \
        .DmaPad={.dma_num = 0, .channel = 10},      \
        .priority = 10,                             \
        .mux = DMA_REQ_FCSDIO_RX,                   \
        .num = 1,                                   \
        .name = "Sdio1rx",                           \
        .aligment_source = DMA_ALIGNMENT_BYTE,      \
        .aligment_destination = DMA_ALIGNMENT_BYTE, \
        .base_addr_source = (uint32_t) fromArray,   \
        .base_addr_destination =(uint32_t) toArray, \
        .block_size = (uint32_t) DMA_MEMCPY_SIZE,   \
        .block_count =1,                            \
        .CallBackHalf= CallBackHalfSdio1Rx,          \
        .CallBackDone= CallBackDoneSdio1Rx,          \
        .dir = DMA_MCAL_DIR_PERIPH_TO_MEMORY,       \
        .inc_destination = DMA_INC_ON,              \
        .per_inc = DMA_INC_OFF,                  \
        .fifo = DMA_FIFO_OFF,                       \
        .mode = DMA_MODE_NORMAL,                    \
        .memory_burst = DMA_BURST_SINGLE,           \
        .periph_burst = DMA_BURST_SINGLE,           \
        .valid = true,                              \
        .interrupt_on = true,                       \
    },

#define DMA_CHANNEL_SDIO_TX                  \
    {                                        \
 .DmaPad={.dma_num = 0,  .channel = 1},      \
 .priority = 1,                              \
 .mux = DMA_REQ_FCSDIO_TX,                   \
 .num = 2,                                   \
 .CallBackHalf= CallBackHalfSdio1Tx,          \
 .CallBackDone= CallBackDoneSdio1Tx,          \
 .block_count =1,                            \
 .dir = DMA_MCAL_DIR_MEMORY_TO_PERIPH,       \
 .mode = DMA_MODE_NORMAL,                    \
 .inc_destination = DMA_INC_ON,              \
 .interrupt_on = true,                       \
 .base_addr_source = (uint32_t)fromArray,    \
 .base_addr_destination =(uint32_t) toArray, \
 .inc_source = DMA_INC_OFF,                  \
 .aligment_source = DMA_ALIGNMENT_BYTE,      \
 .aligment_destination = DMA_ALIGNMENT_BYTE, \
 .fifo = DMA_FIFO_OFF,                       \
 .memory_burst = DMA_BURST_SINGLE,           \
 .periph_burst = DMA_BURST_SINGLE,           \
 .valid = true,                              \
 .name = "Sdio1Tx",                           \
    },




#define DMA_CHANNEL_SDIO \
    DMA_CHANNEL_SDIO_TX  \
    DMA_CHANNEL_SDIO_RX



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_SDIO_CONFIG_H  */
