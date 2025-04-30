#ifndef RV32IMC_COMMANDS_H
#define RV32IMC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_SCR1_TIMER_COMMANDS
#include "scr1_timer_commands.h"
#else
#define SCR1_TIMER_COMMANDS
#endif

bool rv32imc_diag_command(int32_t argc, char* argv[]);
bool rv32imc_reboot_command(int32_t argc, char* argv[]);
bool rv32imc_boot_command(int32_t argc, char* argv[]);

#define RV32IMC_COMMANDS                                             \
    SCR1_TIMER_COMMANDS                                              \
    SHELL_CMD("rv32imc_boot", "rv32b", rv32imc_boot_command, "Rv32imcBoot"), \
    SHELL_CMD("rv32imc_reboot", "rv32r", rv32imc_reboot_command, "Rv32imcReBoot"), \
    SHELL_CMD("rv32imc_diag", "rv32d", rv32imc_diag_command, "Rv32imcDiag"),

#ifdef __cplusplus
}
#endif

#endif /* RV32IMC_COMMANDS_H */
