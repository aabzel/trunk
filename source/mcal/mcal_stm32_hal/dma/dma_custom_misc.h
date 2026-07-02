#ifndef DMA_CUSTOM_MISC_H
#define DMA_CUSTOM_MISC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_types.h"

uint32_t PeriphBurst2StmPeriphBurst(const DmaBurst_t periph_burst) ;
uint32_t DmaGetMode(const DmaMode_t mode) ;
uint32_t DmaGetPriority(const DmaPriority_t priority) ;
uint32_t MemoryBurst2StmMemoryBurst(const uint8_t mem_burst);
uint32_t DmaGetFiFoNode(const DmaFifo_t fifo) ;
uint32_t DmaGetPeriphDataAlignment(const DmaAligmant_t aligment_per) ;
uint32_t DmaGetMemDataAlignment(const DmaAligmant_t aligment_mem) ;
uint32_t DmaGetPeriphInc(const uint8_t per_inc);
uint32_t DmaGetMemInc(const uint8_t mem_inc) ;
uint32_t DmaDirToStm32DmaDir(const DmaDir_t dir) ;


#ifdef __cplusplus
}
#endif


#endif /* DMA_CUSTOM_MISC_H */
