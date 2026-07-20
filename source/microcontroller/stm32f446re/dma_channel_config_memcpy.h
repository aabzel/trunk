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


#define DMA_CHANNEL_MEMCPY1                  \
    {                                        \
 .num = DMA_CHANNEL_NUM_MEMCPY1,             \
 .DmaPad={.dma_num = 1, .channel = 5, },     \
 .priority = 10,                             \
 .mux = 0,                                   \
 .CallBackHalf= CallBackHalfMemCpy,          \
 .CallBackDone= CallBackDoneMemCpy,          \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,       \
 .mode = DMA_MODE_NORMAL,                    \
 .aligment_mem = DMA_ALIGNMENT_BYTE,         \
 .aligment_per = DMA_ALIGNMENT_BYTE,         \
 .per_inc = DMA_INC_ON,                      \
 .mem_inc = DMA_INC_ON,                      \
 .block_count = 1 ,                          \
 .fifo = DMA_FIFO_OFF,                       \
 .interrupt_on = true,                       \
 .memory_burst = DMA_BURST_SINGLE,           \
 .base_addr_source =(uint32_t) fromArray,    \
 .base_addr_destination =(uint32_t) toArray, \
 .periph_burst = DMA_BURST_SINGLE,           \
 .valid = true,                              \
 .name = "MemCpy",                           \
    },


#define DMA_CHANNEL_MEMCPY2                   \
    {                                         \
 .num = DMA_CHANNEL_NUM_MEMCPY2,              \
 .DmaPad={.dma_num = 2, .channel = 4,},       \
 .priority = 3,                               \
 .mux = 0,                                    \
 .CallBackHalf= CallBackHalfMemCpy,           \
 .CallBackDone= CallBackDoneMemCpy,           \
 .dir = DMA_MCAL_DIR_MEMORY_TO_MEMORY,        \
 .mode = DMA_MODE_NORMAL,                     \
 .per_inc = DMA_INC_ON,                       \
 .block_count =1,                             \
 .mem_inc = DMA_INC_ON,                       \
 .aligment_mem = DMA_ALIGNMENT_BYTE,          \
 .aligment_per= DMA_ALIGNMENT_BYTE,           \
 .fifo = DMA_FIFO_OFF,                        \
 .interrupt_on = true,                        \
 .memory_burst = DMA_BURST_SINGLE,            \
 .base_addr_source = (uint32_t)fromArray,     \
 .base_addr_destination = (uint32_t)toArray,  \
 .periph_burst = DMA_BURST_SINGLE,            \
 .valid = true,                               \
 .name = "MemCpy",                            \
    },



#define DMA_CHANNEL_MEMCPY  \
    DMA_CHANNEL_MEMCPY1     \
    DMA_CHANNEL_MEMCPY2



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CONFIG_MEMCPY_H  */
