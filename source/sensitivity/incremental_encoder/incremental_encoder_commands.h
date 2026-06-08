#ifndef INCREMENTAL_ENCODER_COMMANDS_H
#define INCREMENTAL_ENCODER_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_INCREMENTAL_ENCODER
#error "+ HAS_INCREMENTAL_ENCODER"
#endif

#ifndef HAS_INCREMENTAL_ENCODER_COMMANDS
#error "+ HAS_INCREMENTAL_ENCODER_COMMANDS"
#endif

bool incremental_encoder_set_0_command(int32_t argc, char* argv[]);
bool incremental_encoder_diag_command(int32_t argc, char* argv[]);
bool incremental_encoder_init_command(int32_t argc, char* argv[]);

#define INCREMENTAL_ENCODER_COMMANDS                                                                                  \
        SHELL_CMD("incremental_encoder_set_0", "iens0", incremental_encoder_set_0_command, "IncrementalEncoderSetZero"),     \
        SHELL_CMD("incremental_encoder_diag", "iend", incremental_encoder_diag_command, "IncrementalEncoderDiag"),     \
        SHELL_CMD("incremental_encoder_init", "ieni", incremental_encoder_init_command, "IncrementalEncoderInit"),

#ifdef __cplusplus
}
#endif

#endif /* INCREMENTAL_ENCODER_COMMANDS_H */
