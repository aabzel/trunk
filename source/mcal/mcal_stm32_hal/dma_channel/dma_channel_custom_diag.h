#ifndef DMA_CHANNEL_CUSTOM_DIAG_H
#define DMA_CHANNEL_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_custom_types.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

const char* DmaStmPriorityLevelToStr(const DmaStmPriorityLevel_t priority_level);
const char* dma_channel_to_str(uint8_t dma_num, uint8_t stream_num, uint32_t channel) ;
bool dma_channel_diag_custom(void);
bool dma_channel_diag_low_level(char* key_word1, char* key_word2);
const char* DmaStmMoveModeToStr(const DmaStmMoveMode_t move_mode) ;
const char* DmaStmIncrToStr(const DmaStmIncrementMode_t increment_mode);
const char* DmaDirToStr(uint8_t code);
uint8_t DmaStmDataSizeToBits(const DmaStm32Aligmant_t code);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_CUSTOM_DIAG_H  */
