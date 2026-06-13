#ifndef ENCODER_LAMP_COMMANDS_H
#define ENCODER_LAMP_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_ENCODER_LAMP
#error "+ HAS_ENCODER_LAMP"
#endif

#ifndef HAS_ENCODER_LAMP_COMMANDS
#error "+ HAS_ENCODER_LAMP_COMMANDS"
#endif

bool encoder_lamp_diag_command(int32_t argc, char* argv[]);
bool encoder_lamp_init_command(int32_t argc, char* argv[]);

#define ENCODER_LAMP_COMMANDS                                                                \
        SHELL_CMD("encoder_lamp_diag", "swd", encoder_lamp_diag_command, "EncoderLampDiag"), \
        SHELL_CMD("encoder_lamp_init", "swi", encoder_lamp_init_command, "EncoderLampInit"),

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_LAMP_COMMANDS_H */
