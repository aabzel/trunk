#ifndef PLL_CALC_COMMANDS_H
#define PLL_CALC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#define "+HAS_CLI"
#endif

#ifndef HAS_DIAG
#define "+HAS_DIAG"
#endif

bool pll_calc_artery_f413_command(int32_t argc, char* argv[]);
bool pll_calc_artery_f43x_command(int32_t argc, char* argv[]);
bool pll_calc_stm_command(int32_t argc, char* argv[]);

#define PLL_CALC_COMMANDS                                                            \
    SHELL_CMD("pll_calc_at32f413", "plaf413", pll_calc_artery_f413_command, "PllCalcArteryF413"),   \
    SHELL_CMD("pll_calc_at32f43x", "plaf43x", pll_calc_artery_f43x_command, "PllCalcArteryF43x"),   \
    SHELL_CMD("pll_calc_st", "pls", pll_calc_stm_command, "PllCalcStm"),

#ifdef __cplusplus
}
#endif

#endif /* PLL_CALC_COMMANDS_H  */
