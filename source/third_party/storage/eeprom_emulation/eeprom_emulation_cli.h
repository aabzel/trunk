#ifndef EEPROM_EMULATION_CLI_H
#define EEPROM_EMULATION_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_EEPROM_EMULATION
#error "+HAS_EEPROM_EMULATION"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

bool eeprom_emulation_init_cli(int32_t argc, char* argv[]);
bool eeprom_emulation_diag_cli(int32_t argc, char* argv[]);
bool eeprom_emulation_dump_cli(int32_t argc, char* argv[]);
bool eeprom_emulation_erase_cli(int32_t argc, char* argv[]);
bool eeprom_emulation_read_cli(int32_t argc, char* argv[]);
bool eeprom_emulation_write_cli(int32_t argc, char* argv[]);

#define EEPROM_EMULATION_CLI                                                                            \
    SHELL_CMD("eeprom_emulation_init", "eei", eeprom_emulation_init_cli, "EepromEmulationInit"),        \
    SHELL_CMD("eeprom_emulation_dump", "eedu", eeprom_emulation_dump_cli, "EepromEmulationDump"),       \
    SHELL_CMD("eeprom_emulation_diag", "eedi", eeprom_emulation_diag_cli, "EepromEmulationDiag"),       \
    SHELL_CMD("eeprom_emulation_erase", "eee", eeprom_emulation_erase_cli, "EepromEmulationErase"),     \
    SHELL_CMD("eeprom_emulation_read", "eer", eeprom_emulation_read_cli, "EepromEmulationRead"),        \
    SHELL_CMD("eeprom_emulation_write", "eew", eeprom_emulation_write_cli, "EepromEmulationWrite"),

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_EMULATION_CLI_H */
