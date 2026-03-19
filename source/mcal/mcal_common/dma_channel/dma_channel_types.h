#ifndef DMA_CHANNEL_MCAL_TYPES_H
#define DMA_CHANNEL_MCAL_TYPES_H

#include "std_includes.h"
#include "dma_channel_const.h"
#include "dma_channel_general_types.h"
#ifdef HAS_DMA
#include "dma_types.h"
#endif


#ifdef HAS_DMA_CHANNEL_CUSTOM
#include "dma_channel_custom_types.h"
#else
#define DMA_CHANNEL_CUSTOM_VARIABLES
#endif

typedef bool (*DmaIsrHandler_t)(void);

#define DMA_CHANNEL_CALLBACKS                           \
    DmaIsrHandler_t CallBackHalf;                       \
    DmaIsrHandler_t CallBackDone;

#define DMA_CHANNEL_ALIGMENT_VARIABLES                   \
    DmaAligmant_t aligment_source;                       \
    DmaAligmant_t aligment_destination;

#define DMA_CHANNEL_BASE_ADDR_VARIABLES                   \
    uint32_t base_addr_source;    /* base addrress for peripheral source */             \
    uint32_t base_addr_destination;        /* base addrress for memory destination */

#define DMA_CHANNEL_COMMON_INCREMENT_VARIABLES          \
    DmaInc_t inc_destination;                           \
    DmaInc_t inc_source;


#define DMA_CHANNEL_COMMON_VARIABLES                    \
    uint8_t num;                                        \
    DmaChannelPad_t DmaPad;                             \
    DMA_CHANNEL_CALLBACKS                               \
    DMA_CHANNEL_ALIGMENT_VARIABLES                      \
    DMA_CHANNEL_BASE_ADDR_VARIABLES                     \
    DMA_CHANNEL_COMMON_INCREMENT_VARIABLES              \
    uint32_t block_size ;                               \
    uint32_t block_count ;                              \
    DmaDir_t dir;                                       \
    char* name;                                         \
    DmaPriority_t priority;                             \
    uint8_t mux;                                        \
    DmaBurst_t memory_burst;                            \
    DmaBurst_t periph_burst;                            \
    DmaFifo_t fifo;                                     \
    DmaMode_t mode;                                     \
    bool interrupt_on;                                  \
    bool valid;


typedef struct {
    DMA_CHANNEL_COMMON_VARIABLES
}DmaChannelConfig_t;

#define DMA_CHANNEL_ISR_HALF_VARIABLES         \
    volatile bool half;  \
    volatile uint32_t half_cnt;

#define DMA_CHANNEL_ISR_DONE_VARIABLES         \
    volatile bool done;         \
    volatile uint32_t done_cnt;

#define DMA_CHANNEL_ISR_INT_VARIABLES         \
    volatile bool it_done;                    \
    volatile uint32_t it_cnt;

#define DMA_CHANNEL_ISR_ERROR_VARIABLES         \
    volatile bool error_done;                   \
    volatile uint32_t error_cnt;

#define DMA_CHANNEL_ISR_GLOBAL_VARIABLES         \
    volatile bool global_done;           \
    volatile uint32_t global_cnt;

#define DMA_CHANNEL_ISR_VARIABLES         \
    DMA_CHANNEL_ISR_GLOBAL_VARIABLES      \
    DMA_CHANNEL_ISR_HALF_VARIABLES        \
    DMA_CHANNEL_ISR_ERROR_VARIABLES       \
    DMA_CHANNEL_ISR_INT_VARIABLES         \
    DMA_CHANNEL_ISR_DONE_VARIABLES        \
    volatile bool busy;                   \
    volatile bool processed;

typedef struct {
    bool init;
    uint32_t spin;
    DMA_CHANNEL_CUSTOM_VARIABLES
    DMA_CHANNEL_COMMON_VARIABLES
    DMA_CHANNEL_ISR_VARIABLES
}DmaChannelHandle_t;


#endif /* DMA_CHANNEL_MCAL_TYPES_H */
