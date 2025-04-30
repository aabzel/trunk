#include "eeprom_commands.h"

#include "convert.h"
#include "eeprom_mcal.h"
#include "log.h"

bool eeprom_erase_dword_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        log_res(EEPROM, res, "ReadAddr");
    }

    if(res) {
        res = eeprom_dword_erase(address);
        log_res(EEPROM, res, "EraseDword");
    } else {
        LOG_ERROR(EEPROM, "Usage: eed address");
    }
    return res;
}

bool eeprom_dump_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = eeprom_dump();
    log_res(EEPROM, res, "EraseDump");
    return res;
}

bool eeprom_custum_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = eeprom_custum_diag();
    log_res(EEPROM, res, "EraseCustomInit");
    return res;
}

bool eeprom_raw_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = eeprom_raw_reg();
    log_res(EEPROM, res, "EraseRawReg");
    return res;
}
