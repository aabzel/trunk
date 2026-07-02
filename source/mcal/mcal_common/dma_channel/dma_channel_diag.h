#ifndef DMA_CHANNEL_DIAG_H
#define DMA_CHANNEL_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_channel_types.h"

#ifdef HAS_DMA_CUSTOM_DIAG
#include "dma_custom_diag.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_DMA_CHANNEL
#error "+HAS_DMA_CHANNEL"
#endif

#ifndef HAS_DMA_CHANNEL_DIAG
#error "+HAS_DMA_CHANNEL_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool dma_channel_diag(void);
//const char* DmaPadToStr(const DmaChannelPad_t DmaPad) ;
const char* DmaInfoPadToStr(const DmaInfoChannel_t * const pDmaPad) ;
const char* DmaChannnelNumToStr(uint8_t num);
const char* DmaChannelMuxToStr(uint8_t mux);
const char* DmaChannelConfigToStr(const DmaChannelConfig_t* const Config);
const char* DmaChannelNodeToStr(const DmaChannelHandle_t* const Node);
const char* DmaChannelCtrlNodeToStr(const DmaChannelHandle_t* const Node);
const char* DmaChannelConfigSrcToStr(const DmaChannelConfig_t* const Config);
const char* DmaChannelIsrInfo(const DmaChannelHandle_t* const Node);
const char* DmaChannelConfigDesToStr(const DmaChannelConfig_t* const Config);
#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_DIAG_H  */
