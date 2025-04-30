#ifndef EEPROM_COMMANDS_H
#define EEPROM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_EEPROM_CUSTOM
#include "eeprom_custom_commands.h"
#else
#define EEPROM_CUSTOM_COMMANDS
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_EEPROM
#error "+HAS_EEPROM"
#endif

#ifndef HAS_STORAGE
#error "+HAS_STORAGE"
#endif

bool eeprom_write_relatively_command(int32_t argc, char* argv[]);
bool eeprom_read_relatively_command(int32_t argc, char* argv[]);
bool eeprom_diag_cmd(int32_t argc, char* argv[]);
bool eeprom_init_cmd(int32_t argc, char* argv[]);
bool eeprom_scan_cmd(int32_t argc, char* argv[]);
bool eeprom_read_cmd(int32_t argc, char* argv[]);
bool eeprom_write_cmd(int32_t argc, char* argv[]);
bool eeprom_erase_cmd(int32_t argc, char* argv[]);

#define EEPROM_COMMANDS                                                                                    \
    EEPROM_CUSTOM_COMMANDS                                                                                 \
    SHELL_CMD("eeprom_diag", "ed", eeprom_diag_cmd, "EepromDiag"),                                         \
    SHELL_CMD("eeprom_read_relative", "err", eeprom_read_relatively_command, "EepromReadRalative"),        \
    SHELL_CMD("eeprom_write_relative", "ewr", eeprom_write_relatively_command, "EepromWriteRalative"),     \
    SHELL_CMD("eeprom_init", "ei", eeprom_init_cmd, "EepromInit"),                                         \
    SHELL_CMD("eeprom_write", "ew", eeprom_write_cmd, "EepromWrite"),                                      \
    SHELL_CMD("eeprom_read", "er", eeprom_read_cmd, "EepromRead"),                                         \
    SHELL_CMD("eeprom_erase", "ee", eeprom_erase_cmd, "EepromErase"),                                      \
    SHELL_CMD("eeprom_scan", "es", eeprom_scan_cmd, "EepromScan"),

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_COMMANDS_H */
