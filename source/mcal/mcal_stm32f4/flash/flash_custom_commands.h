#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool flash_diag_reg_command(int32_t argc, char* argv[]);
bool flash_diag_command(int32_t argc, char* argv[]);
bool flash_stm_diag_reg_command(int32_t argc, char* argv[]) ;
bool flash_scan_command(int32_t argc, char* argv[]);
bool flash_mcal_writeite_command(int32_t argc, char* argv[]);
bool flash_mcal_erasecommand(int32_t argc, char* argv[]);

#define FLASH_CUSTOM_COMMANDS                                                                                                 \
    SHELL_CMD("flash_diag", "fcd", flash_diag_command, "FlashCustomDiag"),                                                   \
        SHELL_CMD("flash_diag_reg", "fdr", flash_stm_diag_reg_command, "FlashCustomDiagReg"),                                      \
        SHELL_CMD("flash_mcal_writeite", "fcw", flash_mcal_writeite_command, "FlashCustomWrite"),                                            \
        SHELL_CMD("flash_erase", "fce", flash_mcal_erasecommand, "FlashCustomErase"),                                            \
        SHELL_CMD("flash_scan", "fcs", flash_scan_command, "FlashCustomScan"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */
