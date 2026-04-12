#ifndef WRITER_COMMANDS_H
#define WRITER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_WRITER
#error "+ HAS_WRITER"
#endif

#ifndef HAS_WRITER_COMMANDS
#error "+ HAS_WRITER_COMMANDS"
#endif

bool writer_diag_command(int32_t argc, char* argv[]);
bool writer_init_command(int32_t argc, char* argv[]);

#define WRITER_COMMANDS                                                                                    \
        SHELL_CMD("writer_diag", "wd", writer_diag_command, "WriterDiag"),                           \
        SHELL_CMD("writer_init", "wi", writer_init_command, "WriterInit"),

#ifdef __cplusplus
}
#endif

#endif /* WRITER_COMMANDS_H */
