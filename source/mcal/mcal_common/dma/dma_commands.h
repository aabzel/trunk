#ifndef DMA_COMMANDS_H
#define DMA_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_DMA_CUSTOM_COMMANDS
#include "dma_custom_commands.h"
#else
#define DMA_CUSTOM_COMMANDS
#endif

#ifndef HAS_DMA_COMMANDS
#error "+HAS_DMA_COMMANDS"
#endif

bool dma_start_command(int32_t argc, char* argv[]);
bool dma_stop_command(int32_t argc, char* argv[]);
bool dma_init_command(int32_t argc, char* argv[]);
bool dma_diag_command(int32_t argc, char* argv[]);

#define DMA_COMMANDS                                                  \
    DMA_CUSTOM_COMMANDS                                               \
    SHELL_CMD("dma_start", "dt", dma_start_command, "DmaStart"),      \
    SHELL_CMD("dma_stop", "ds", dma_stop_command, "DmaStop"),      \
    SHELL_CMD("dma_init", "di", dma_init_command, "DmaInit"),      \
    SHELL_CMD("dma_diag", "dd", dma_diag_command, "DmaDiag"),

#ifdef __cplusplus
}
#endif

#endif /* DMA_COMMANDS_H */
