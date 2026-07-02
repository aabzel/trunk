#ifndef DMA_CHANNEL_STM_CONST_H
#define DMA_CHANNEL_STM_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_custom_dep.h"

/*
Bits 14:13 MSIZE[1:0]: Memory data size
Bits 12:11 PSIZE[1:0]: Peripheral data size
 * */
typedef enum {
    DMA_STM32_ALIGNMENT_BYTE = 0,       /* 00: Byte (8-bit)        */
    DMA_STM32_ALIGNMENT_HALF_WORD = 1,  /* 01: Half-word (16-bit)  */
    DMA_STM32_ALIGNMENT_WORD = 2,       /* 10: Word (32-bit)       */
    DMA_STM32_ALIGNMENT_RESERVED = 3,   /* 11: reserved            */
    DMA_STM32_ALIGNMENT_UNDEF = 4,      /* */
} DmaStm32Aligmant_t;

/* Bits 7:6 DIR[1:0]: Data transfer direction   */
typedef enum {
    DMA_STM32_DIR_PERIPHERAL_TO_MEMORY  = 0,  /* 00: Peripheral-to-memory  */
    DMA_STM32_DIR_MEMORY_TO_PERIPHERAL = 1,   /* 01: Memory-to-peripheral */
    DMA_STM32_DIR_MEMORY_TO_MEMORY = 2,       /* 10: Memory-to-memory */
    DMA_STM32_DIR_RESERVED = 3,               /* 11: reserved */
    DMA_STM32_DIR_UNDEF =4,
} DmaStmDataTransferDirection_t;


/*
  Bit 9  PINC: Peripheral increment mode
  Bit 10 MINC: Memory increment mode
 */
typedef enum {
    DMA_STM32_INCR_MODE_OFF   = 0 , /*0: Peripheral address pointer is fixed*/
    DMA_STM32_INCR_MODE_ON   = 1 , /*1: Peripheral address pointer is incremented after
                                        each data transfer (increment is done according to PSIZE)*/
    DMA_STM32_INCR_MODE_UNDEF = 2,
} DmaStmIncrementMode_t;


/* Bit 8 CIRC: Circular mode */
typedef enum {
    DMA_STM32_MOVE_MODE_NORMAL   = 0 ,   /* 0: Circular mode disabled */
    DMA_STM32_MOVE_MODE_CIRCULAR   = 1 , /* 1: Circular mode enabled*/
    DMA_STM32_MOVE_MODE_UNDEF = 2,
} DmaStmMoveMode_t;

/*Bits 17:16 PL[1:0]: Priority level*/
typedef enum {
    DMA_STM32_PRIORITY_LEVEL_LOW   = 0 , /* 00: Low */
    DMA_STM32_PRIORITY_LEVEL_MEDIUM   = 1 ,   /* 01: Medium */
    DMA_STM32_PRIORITY_LEVEL_HIGH = 2, /* 10: High */
    DMA_STM32_PRIORITY_LEVEL_VERY_HIGH = 3, /* 11: Very high */
    DMA_STM32_PRIORITY_LEVEL_UNDEF = 3, /* */
} DmaStmPriorityLevel_t;



#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_STM_CONST_H  */
