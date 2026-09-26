#ifndef DMA_CHANNEL_CONFIG_MEMCPY_H
#define DMA_CHANNEL_CONFIG_MEMCPY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

#define DMA_MEMCPY_SIZE 50
extern uint8_t toArray[DMA_MEMCPY_SIZE];
extern uint8_t fromArray[DMA_MEMCPY_SIZE];

bool CallBackHalfMemCpy(void);
bool CallBackDoneMemCpy(void);


#define DMA_CHANNEL_MEMCPY_COMMON            \
 .mem_inc = DMA_INC_ON,                      \
 .mode = DMA_MODE_NORMAL,                    \
 .block_count = 1 ,                          \
 .periph_burst = DMA_BURST_SINGLE,           \
 .fifo = DMA_FIFO_OFF,                       \
 .interrupt_on = true,                       \
 .aligment_mem = DMA_ALIGNMENT_BYTE,         \
 .aligment_per = DMA_ALIGNMENT_BYTE,         \
 .memory_burst = DMA_BURST_SINGLE,           \
 .per_inc = DMA_INC_ON,                      \
 .valid = true,                              \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,       \
 .priority = 5,                              \
 .mux = 0,

#define DMA_CHANNEL_MEMCPY1                            \
    {                                                  \
    DMA_CHANNEL_MEMCPY_COMMON                          \
 .num = DMA_CHANNEL_NUM_MEMCPY1,                       \
 .DmaChPad={.dma_num = 2, .stream=1, .channel = 0, },  \
 .CallBackHalf= CallBackHalfMemCpy,                    \
 .CallBackDone= CallBackDoneMemCpy,                    \
 .base_addr_source =(uint32_t) fromArray,              \
 .base_addr_destination =(uint32_t) toArray,           \
 .name = "MemCpy",                                     \
    },


#define DMA_CHANNEL_MEMCPY2                            \
    {                                                  \
        DMA_CHANNEL_MEMCPY_COMMON                      \
 .num = DMA_CHANNEL_NUM_MEMCPY2,                       \
 .DmaChPad={.dma_num = 2, .stream=3, .channel = 0,},   \
 .CallBackHalf= CallBackHalfMemCpy,                    \
 .CallBackDone= CallBackDoneMemCpy,                    \
 .base_addr_source = (uint32_t)fromArray,              \
 .base_addr_destination = (uint32_t)toArray,           \
 .name = "MemCpy",                                     \
    },

#define DMA_CHANNEL_MEMCPY  \
    DMA_CHANNEL_MEMCPY1     \
    DMA_CHANNEL_MEMCPY2



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_MEMCPY_H  */
