#ifndef DMA_COMMANDS_H
#define DMA_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DMA_COMMANDS
#include "dma_custom_commands.h"
#else
#define DMA_CUSTOM_COMMANDS
#endif

#ifndef HAS_DMA_COMMANDS
#error "+HAS_DMA_COMMANDS"
#endif

bool dma_diag_command(int32_t argc, char* argv[]);
#if 0
bool dma_channel_diag_command(int32_t argc, char* argv[]);
bool dma_channel_mux_command(int32_t argc, char* argv[]);
#endif

#define DMA_COMMANDS DMA_CUSTOM_COMMANDS                                               \
    SHELL_CMD("dma_diag", "dd", dma_diag_command, "DmaDiag"),

#if 0
    SHELL_CMD("dma_channel_mux", "dcm", dma_channel_mux_command, "DmaChannelMux"),     \
    SHELL_CMD("dma_channel_diag", "dcd", dma_channel_diag_command, "DmaChannelDiag"),
#endif



#ifdef __cplusplus
}
#endif

#endif /* DMA_COMMANDS_H */
