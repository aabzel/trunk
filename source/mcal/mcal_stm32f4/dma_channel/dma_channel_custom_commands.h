#ifndef DMA_CUSTOM_COMMANDS_H
#define DMA_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

#ifndef HAS_DMA_COMMANDS
#error "+HAS_DMA_COMMANDS"
#endif

//bool dma_diag_stream_command(int32_t argc, char* argv[]);

#define DMA_CHANNEL_CUSTOM_COMMANDS
//    SHELL_CMD("dma_diag_stream", "dds", dma_diag_stream_command, "DmaDiagStream"),

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_COMMANDS_H */
