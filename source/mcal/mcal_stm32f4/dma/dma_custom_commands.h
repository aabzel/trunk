#ifndef DMA_CUSTOM_COMMANDS_H
#define DMA_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

#ifndef HAS_DMA_COMMANDS
#error "+HAS_DMA_COMMANDS"
#endif

//bool dma_diag_low_level_command(int32_t argc, char* argv[]);
//bool dma_diag_stream_command(int32_t argc, char* argv[]);

#define DMA_CUSTOM_COMMANDS
//    SHELL_CMD("dma_diag", "dd", dma_diag_command, "DmaDiag"),
//    SHELL_CMD("dma_diag_ll", "ddl", dma_diag_low_level_command, "DmaDiagLowLevel"),
//    SHELL_CMD("dma_diag_stream", "dds", dma_diag_stream_command, "DmaDiagStream"),
//    SHELL_CMD("dma_init", "di", dma_init_command, "DmaInit"),
//    SHELL_CMD("dma_stop", "ds", dma_stop_command, "DmaStop"),

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_COMMANDS_H */
