#ifndef DMA_MCAL_TYPES_H
#define DMA_MCAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "dma_const.h"
#ifdef HAS_DMA_COSTOM
#include "dma_custom_types.h"
#else
#define DMA_CUSTOM_TYPES
#endif

//Table 9-3 Flexible DMA1/DMA2 request mapping
typedef struct {
    uint8_t mux;
    bool valid;
    char* name;
}DmaMuxInfo_t;

typedef union{
    uint8_t byte;
    struct{
        uint8_t dma_num:2; // 0[1,2]..3
        uint8_t channel:6; // 0,[1...7]...63
    };
}DmaPad_t;

#define DMA_STREAM           \
    DmaChannel_t channel;    \
    uint8_t dma_num;

typedef struct {
    DMA_STREAM
}DmaStream_t;

#define DMA_COMMON_VARIABLES     \
    uint8_t num;                 \
    uint8_t dma_num;             \
    char* name;                  \
    bool valid;


typedef struct {
    DMA_COMMON_VARIABLES
} DmaConfig_t;

typedef struct {
    DMA_COMMON_VARIABLES
    DMA_CUSTOM_TYPES
    bool init;
} DmaHandle_t;


typedef bool (*DmaIsrHandler_t)(void);

#define DMA_CHANNEL_COMMON_VARIABLES            \
    DmaIsrHandler_t CallBackHalf;             \
    DmaIsrHandler_t CallBackDone;             \
    DmaBurst_t memory_burst;   \
    DmaBurst_t periph_burst;   \
    char* name;                  \
    DmaFifo_t fifo;                  \
    DmaMode_t mode;                     \
    DmaDir_t dir;                       \
    DmaInc_t mem_inc;                   \
    DmaInc_t per_inc;                   \
    DmaPriority_t priority;             \
    uint32_t peripheral_base_addr;    /* base addrress for peripheral */             \
    uint32_t memory_base_addr;        /* base addrress for memory */             \
    uint16_t buffer_size;  /*counter to transfer (0~0xFFFF)    */         \
    DmaAligmant_t aligment_per;             \
    DmaAligmant_t aligment_mem;             \
    DmaChannel_t channel;             \
    uint8_t dma_num;                  \
    uint8_t num;                      \
    uint8_t mux;                      \
    bool valid;

typedef struct  {
    DMA_CHANNEL_COMMON_VARIABLES
} DmaChannelConfig_t ;

#define DMA_CHANNEL_ISR_VARIABLES         \
    volatile bool global_done;         \
    volatile bool it_done;         \
    volatile bool it_error;         \
    volatile bool half;         \
    volatile bool done;         \
    volatile bool busy;            \
    volatile uint32_t it_cnt;         \
    volatile uint32_t half_cnt;         \
    volatile uint32_t done_cnt;         \
    volatile uint32_t error_cnt;         \
    volatile uint32_t global_cnt;


typedef struct {
    DMA_CHANNEL_COMMON_VARIABLES
    DMA_CHANNEL_ISR_VARIABLES
    bool init;
} DmaChannelHandle_t ;



#ifdef __cplusplus
}
#endif

#endif /* DMA_MCAL_TYPES_H  */
