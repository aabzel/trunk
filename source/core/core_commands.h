#ifndef CORE_COMMANDS_H
#define CORE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_RV32IMC_COMMANDS
#include "rv32imc_commands.h"
#else
#define RV32IMC_COMMANDS
#endif


#ifdef HAS_DWT_COMMANDS
#include "dwt_commands.h"
#else
#define DWT_COMMANDS
#endif

#ifdef HAS_ARM
#include "cortex_commands.h"
#else
#define CORTEX_COMMANDS
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool cmd_try_stack(int32_t argc, char* argv[]);
bool stack_print_command(int32_t argc, char* argv[]);

#define CORE_STACK_COMMANDS                                                       \
    SHELL_CMD("try_stack", "tstk", cmd_try_stack, "ExploreStackRAM"),             \
    SHELL_CMD("stack_print", "stkt", stack_print_command, "StackPrint"),

bool core_exeption_command(int32_t argc, char* argv[]);
bool cmd_soft_reboot(int32_t argc, char* argv[]);
bool core_diag_command(int32_t argc, char* argv[]);
bool core_check_address_command(int32_t argc, char* argv[]);
bool core_address_offset_command(int32_t argc, char* argv[]);

#define CORE_COMMANDS                                                             \
    CORE_CORTEX_M_COMMANDS                                                        \
    RV32IMC_COMMANDS                                                              \
    DWT_COMMANDS                                                                  \
    CORE_STACK_COMMANDS                                                              \
    SHELL_CMD("core_check_address", "ca", core_check_address_command, "CoreCheckAddr"),                  \
    SHELL_CMD("core_address_offset", "cao", core_address_offset_command, "CoreAddrOffset"),                  \
    SHELL_CMD("core_diag", "cd", core_diag_command, "CoreDiag"),                  \
    SHELL_CMD("soft_reboot", "reboot", cmd_soft_reboot, "RebootCore"),

#ifdef __cplusplus
}
#endif

#endif /* CORE_COMMANDS_H */
