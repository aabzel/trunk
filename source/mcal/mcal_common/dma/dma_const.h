#ifndef DMA_MCAL_CONST_H
#define DMA_MCAL_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_dep.h"

#define DMA_TRANSFER_TIMEOUT_MS 4000

/*rename to abstract channel type*/
typedef enum {
    DMA_CHAN_0  = 0,
    DMA_CHAN_1  = 1,
    DMA_CHAN_2  = 2,
    DMA_CHAN_3  = 3,
    DMA_CHAN_4  = 4,
    DMA_CHAN_5  = 5,
    DMA_CHAN_6  = 6,
    DMA_CHAN_7  = 7,
    DMA_CHAN_8  = 8,
    DMA_CHAN_9  = 9,
    DMA_CHAN_10 = 10,
    DMA_CHAN_11 = 11,
    DMA_CHAN_12 = 12,
    DMA_CHAN_13 = 13,
    DMA_CHAN_14 = 14,
    DMA_CHAN_15 = 15,

    DMA_CHAN_UNDEF = 16
} DmaChannel_t;

typedef enum {
    DMA_MCAL_DIR_PERIPH_TO_MEMORY = 1,
    DMA_MCAL_DIR_MEMORY_TO_PERIPH = 2,
    DMA_MCAL_DIR_MEMORY_TO_MEMORY = 3,

    DMA_MCAL_DIR_UNDEF = 0,
} DmaDir_t;

typedef enum  {
    DMA_INC_OFF=0,
    DMA_INC_ON=1,

    DMA_INC_UNDEF=2,
} DmaInc_t;

typedef enum {
    DMA_MODE_NORMAL = 1,
    DMA_MODE_CIRCULAR = 2,
    DMA_MODE_PFCTRL = 3, /*??*/

    DMA_MODE_UNDEF = 0,
} DmaMode_t;

typedef enum {
    DMA_ALIG_BYTE=1,
    DMA_ALIG_HALF_WORD=2,
    DMA_ALIG_WORD=4,

    DMA_ALIG_UNDEF=0,
} DmaAligmant_t;

typedef enum  {
	DMA_BURST_SINGLE=0,
	DMA_BURST_INC4=1,
	DMA_BURST_INC8=2,
	DMA_BURST_INC16=3,
} DmaBurst_t;

typedef enum  {
    DMA_PRIOR_LOW=1,
    DMA_PRIOR_MED=2,
    DMA_PRIOR_HIGH=3,
    DMA_PRIOR_VERY_HIGH=4,

    DMA_PRIOR_UNDEF=0,
} DmaPriority_t;

typedef enum {
    DMA_1=1,
    DMA_2=2,

    DMA_UNDEF=0,
} Dma_t;

typedef enum  {
    DMA_FIFO_OFF=1,
    DMA_FIFO_ON=2,

    DMA_FIFO_UNDEF=0,
} DmaFifo_t;

#ifdef __cplusplus
}
#endif

#endif /* DMA_MCAL_CONST_H  */
