#ifndef PDM_COMMANDS_H
#define PDM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_PDM
#error "+HAS_PDM"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_PDM_COMMANDS
#error "+HAS_PDM_COMMANDS"
#endif

#ifdef HAS_PDM_CUSTOM_COMMANDS
#include "pdm_custom_commands.h"
#else
#define PDM_CUSTOM_COMMANDS
#endif

bool pdm_diag_command(int32_t argc, char* argv[]);
bool pdm_calc_dft_command(int32_t argc, char* argv[]);
bool pdm_ctrl_command(int32_t argc, char* argv[]);
bool pdm_init_command(int32_t argc, char* argv[]);
bool pdm_sample_get_command(int32_t argc, char* argv[]);
bool pdm_listen_command(int32_t argc, char* argv[]);

#define PDM_COMMANDS                                                              \
    PDM_CUSTOM_COMMANDS                                                           \
    SHELL_CMD("pdm_listen", "pdl", pdm_listen_command, "PdmListen"),              \
    SHELL_CMD("pdm_diag", "pdd", pdm_diag_command, "PdmDiag"),                    \
    SHELL_CMD("pdm_calc_dft", "pdf", pdm_calc_dft_command, "PdmCalcDft"),         \
    SHELL_CMD("pdm_ctrl", "pdc", pdm_ctrl_command, "PdmCtrl"),                    \
    SHELL_CMD("pdm_init", "pdi", pdm_init_command, "PdmInit"),                    \
    SHELL_CMD("pdm_sample_get", "pdg", pdm_sample_get_command, "PdmSampleGet"),

#ifdef __cplusplus
}
#endif

#endif /* PDM_CUSTOM_COMMANDS_H */
