#ifndef IR_RECEIVER_COMMANDS_H
#define IR_RECEIVER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_IR_RECEIVER
#error "+ HAS_IR_RECEIVER"
#endif

#ifndef HAS_IR_RECEIVER_COMMANDS
#error "+ HAS_IR_RECEIVER_COMMANDS"
#endif

bool ir_receiver_diag_command(int32_t argc, char* argv[]);
bool ir_receiver_init_command(int32_t argc, char* argv[]);

#define IR_RECEIVER_COMMANDS                                                                                          \
        SHELL_CMD("ir_receiver_diag", "ird", ir_receiver_diag_command, "IrReceiverDiag"),                           \
        SHELL_CMD("ir_receiver_init", "iri", ir_receiver_init_command, "IrReceiverInit"),

#ifdef __cplusplus
}
#endif

#endif /* IR_RECEIVER_COMMANDS_H */
