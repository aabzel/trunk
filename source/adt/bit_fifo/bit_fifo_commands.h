#ifndef BIT_FIFO_COMMANDS_H
#define BIT_FIFO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_BIT_FIFO
#error "+ HAS_BIT_FIFO"
#endif

#ifndef HAS_BIT_FIFO_COMMANDS
#error "+ HAS_BIT_FIFO_COMMANDS"
#endif

bool bit_fifo_diag_command(int32_t argc, char* argv[]);
bool bit_fifo_init_command(int32_t argc, char* argv[]);

#define BIT_FIFO_COMMANDS                                                                                          \
        SHELL_CMD("bit_fifo_diag", "bfd", bit_fifo_diag_command, "BitFifoDiag"),                           \
        SHELL_CMD("bit_fifo_init", "bfi", bit_fifo_init_command, "BitFifoInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* BIT_FIFO_COMMANDS_H */
