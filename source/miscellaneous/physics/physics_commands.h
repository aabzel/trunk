#ifndef PHYSICS_COMMANDS_H
#define PHYSICS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_PHYSICS
#error "+ HAS_PHYSICS"
#endif /**/

#ifndef HAS_PHYSICS_COMMANDS
#error "+ HAS_PHYSICS_COMMANDS"
#endif /**/

bool phy_lc_loop_calc_l_command(int32_t argc, char* argv[]);

#define PHYSICS_COMMANDS                                                                   \
    SHELL_CMD("phy_lc_loop_calc_l", "plcl", phy_lc_loop_calc_l_command, "PhyLCloopCalcL"),

#ifdef __cplusplus
}
#endif

#endif /* PHYSICS_COMMANDS_H */
