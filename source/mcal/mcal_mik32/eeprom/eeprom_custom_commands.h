#ifndef EEPROM_CUSTOM_COMMANDS_H
#define EEPROM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool eeprom_custum_diag_command(int32_t argc, char* argv[]) ;
bool eeprom_dump_command(int32_t argc, char* argv[]) ;
bool eeprom_raw_reg_command(int32_t argc, char* argv[]) ;
bool eeprom_erase_dword_command(int32_t argc, char* argv[]) ;

#define EEPROM_CUSTOM_COMMANDS                                                                        \
    SHELL_CMD("eeprom_erase_dword", "eed", eeprom_erase_dword_command, "EepromEraseDword"),           \
    SHELL_CMD("eeprom_dump", "ep", eeprom_dump_command, "EepromDump"),                                \
    SHELL_CMD("eeprom_raw_reg", "eerr", eeprom_raw_reg_command, "EepromRawReg"),                      \
    SHELL_CMD("eeprom_custum_diag", "ecd", eeprom_custum_diag_command, "EepromCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_CUSTOM_COMMANDS_H */
