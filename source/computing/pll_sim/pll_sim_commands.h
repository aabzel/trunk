#ifndef PLL_SIM_COMMANDS_H
#define PLL_SIM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool pll_sim_n_command(int32_t argc, char* argv[]);
bool pll_sim_diag_command(int32_t argc, char* argv[]);

#define PLL_SIM_COMMANDS                                                   \
    SHELL_CMD("pll_sim_n", "psn", pll_sim_n_command, "PllSimN"),           \
    SHELL_CMD("pll_sim_diag", "psd", pll_sim_diag_command, "PllSimDiag"),


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*PLL_SIM_COMMANDS_H*/
