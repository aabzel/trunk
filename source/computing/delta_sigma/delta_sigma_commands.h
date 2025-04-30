#ifndef DELTA_SIGMA_COMMANDS_H
#define DELTA_SIGMA_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


bool delta_sigma_diag_command(int32_t argc, char* argv[]);
bool delta_sigma_target_command(int32_t argc, char* argv[]);

#define DELTA_SIGMA_COMMANDS                                                                \
    SHELL_CMD("delta_sigma_target", "dst", delta_sigma_target_command, "DeltaSigmaTarget"), \
    SHELL_CMD("delta_sigma_diag", "dsd", delta_sigma_diag_command, "DeltaSigmaDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*DELTA_SIGMA_COMMANDS_H*/
