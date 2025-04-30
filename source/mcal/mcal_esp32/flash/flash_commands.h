#ifndef FLASH_COMMANDS_H
#define FLASH_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool flash_diag_command(int32_t argc, char* argv[]);
bool flash_scan_command(int32_t argc, char* argv[]);
bool flash_read_command(int32_t argc, char* argv[]);
bool flash_mcal_writeite_command(int32_t argc, char* argv[]);
bool flash_mcal_erasecommand(int32_t argc, char* argv[]);

#define FLASH_COMMANDS                                                                                                 \
    SHELL_CMD("flash_diag", "fd", flash_diag_command, "Flash diag"),                                                   \
        SHELL_CMD("flash_mcal_writeite", "fw", flash_mcal_writeite_command, "Flash write"),                                            \
        SHELL_CMD("flash_read", "fr", flash_read_command, "Flash read"),                                               \
        SHELL_CMD("flash_erase", "fe", flash_mcal_erasecommand, "Flash erase"),                                            \
        SHELL_CMD("flash_scan", "fs", flash_scan_command, "Flash scan"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_COMMANDS_H */
