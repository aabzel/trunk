#ifndef SW_COMPONENT_COMMANDS_H
#define SW_COMPONENT_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_SW_COMPONENT_CUSTOM_COMMANDS
#include "sw_component_custom_commands.h"
#else
#define SW_COMPONENT_CUSTOM_COMMANDS
#endif


#ifndef HAS_SW_COMPONENT
#error "+ HAS_SW_COMPONENT"
#endif

#ifndef HAS_SW_COMPONENT_COMMANDS
#error "+ HAS_SW_COMPONENT_COMMANDS"
#endif

bool sw_component_diag_command(int32_t argc, char* argv[]);
bool sw_component_init_command(int32_t argc, char* argv[]);
bool sw_component_reg_map_command(int32_t argc, char* argv[]);

#define SW_COMPONENT_COMMANDS                                                                                          \
        SW_COMPONENT_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("sw_component_diag", "swd", sw_component_diag_command, "SwComponentDiag"),                           \
        SHELL_CMD("sw_component_init", "swi", sw_component_init_command, "SwComponentInit"),                           \
        SHELL_CMD("sw_component_reg_map", "swrm", sw_component_reg_map_command, "SwComponentRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* SW_COMPONENT_COMMANDS_H */
