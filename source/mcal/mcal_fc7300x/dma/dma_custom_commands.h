#ifndef DMA_CUSTOM_COMMANDS_H
#define DMA_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_DMA_COMMANDS
#error "+HAS_DMA_COMMANDS"
#endif

bool dma_diag_custom_command(int32_t argc, char* argv[]);
bool dma_channel_diag_custom_command(int32_t argc, char* argv[]);

#define DMA_CUSTOM_COMMANDS                                                        \
    SHELL_CMD("dma_diag_custom", "ddc", dma_diag_custom_command, "DmaDiagCustom"), \
    SHELL_CMD("dma_channel_diag_custom", "dcc", dma_channel_diag_custom_command, "DmaChannelDiagCustom"),


#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_COMMANDS_H */
