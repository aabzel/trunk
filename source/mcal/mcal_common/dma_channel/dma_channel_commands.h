#ifndef DMA_CHANNEL_COMMANDS_H
#define DMA_CHANNEL_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DMA_CHANNEL_COMMANDS
#error "+HAS_DMA_CHANNEL_COMMANDS"
#endif

#ifdef HAS_DMA_CHANNEL_CUSTOM_COMMANDS
#include "dma_channel_custom_commands.h"
#else
#define DMA_CHANNEL_CUSTOM_COMMANDS
#endif

#ifndef HAS_DMA_CHANNEL
#error "+ HAS_DMA_CHANNEL"
#endif

#ifndef HAS_DMA_CHANNEL_COMMANDS
#error "+ HAS_DMA_CHANNEL_COMMANDS"
#endif

bool dma_channel_priority_command(int32_t argc, char* argv[]) ;
bool dma_channel_mux_command(int32_t argc, char* argv[]);
bool dma_channel_diag_command(int32_t argc, char* argv[]);
bool dma_channel_init_command(int32_t argc, char* argv[]);
bool dma_channel_reg_map_command(int32_t argc, char* argv[]);

#define DMA_CHANNEL_COMMANDS                                                                                          \
        DMA_CHANNEL_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("dma_channel_priority", "dcp", dma_channel_priority_command, "DmaChannelPriority"),                 \
        SHELL_CMD("dma_channel_diag", "dcd", dma_channel_diag_command, "DmaChannelDiag"),                             \
        SHELL_CMD("dma_channel_mux", "dcm", dma_channel_mux_command, "DmaChannelMux"),                                \
        SHELL_CMD("dma_channel_init", "dci", dma_channel_init_command, "DmaChannelInit"),                             \
        SHELL_CMD("dma_channel_reg_map", "dcrm", dma_channel_reg_map_command, "DmaChannelRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* DMA_CHANNEL_COMMANDS_H */
