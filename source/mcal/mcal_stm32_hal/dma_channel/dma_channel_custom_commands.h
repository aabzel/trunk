#ifndef DMA_CHANNEL_CUSTOM_COMMANDS_H
#define DMA_CHANNEL_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DMA_CHANNEL_CUSTOM
#error "+HAS_DMA_CHANNEL_CUSTOM"
#endif

#ifndef HAS_DMA_CHANNEL_CUSTOM_COMMANDS
#error "+HAS_DMA_CHANNEL_CUSTOM_COMMANDS"
#endif

bool dma_channel_diag_ll_command(int32_t argc, char* argv[]);
bool dma_channel_diag_custom_command(int32_t argc, char* argv[]);

#define DMA_CHANNEL_CUSTOM_COMMANDS                                                                     \
    SHELL_CMD("dma_channel_diag_ll", "dcdll", dma_channel_diag_ll_command, "DmaChannelDiagLowLevel"),   \
    SHELL_CMD("dma_channel_diag_custom", "dcdc", dma_channel_diag_custom_command, "DmaChannelDiag"),

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_COMMANDS_H */
