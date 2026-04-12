#include "eeprom_emulation_cli.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "convert.h"
#include "log.h"
#include "mcal_to_ehal.h"
#include "eeprom_emulation_diagnostic.h"
#include "eeprom_emulation.h"
#include "eeprom_emulation_ext.h"

bool eeprom_emulation_init_cli(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        EMEEP_Init();
        log_res(EEPROM_EMULATION,res,"Init");
    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eei");
    }

    return res;
}

bool eeprom_emulation_diag_cli(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        STD_RESULT ret = EEPROM_EMULATION_Diag();
        res = EHAL_RetToRes(ret);
        log_res(EEPROM_EMULATION,res,"Diag");
    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eed");
    }

    return res;
}

bool eeprom_emulation_erase_cli(int32_t argc, char* argv[]) {
    bool res = false;
    U32 flashAddr = 0;
    U32 size = 0;
    if(1 <= argc) {
            res = try_str2uint32(argv[0], &flashAddr);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "ParseErr FlashAddr %s", argv[0]);
            }
    }

    if(2 <= argc) {
            res = try_str2uint32(argv[1], &size);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "ParseErr FlashAddr %s", argv[1]);
            }
    }

    if(res) {
        STD_RESULT ret = EMEEP_Erase(flashAddr, size);
        res = EHAL_RetToRes(ret);
        log_res(EEPROM_EMULATION,res,"Erase");
    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eee FlashAddr size");
    }

    return res;
}


/*
eer 0 5
eer 0x081E0000 5
 */
bool eeprom_emulation_read_cli(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t numBytes = 0;
    uint32_t flashAddr = 0;
    if(2 == argc) {
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &flashAddr);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "ParseErr flashAddr %s", argv[0]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[1], &numBytes);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "ParseErr numBytes %s", argv[1]);
            }
        }
    }

    if(res) {
        LOG_INFO(EEPROM_EMULATION, "Read Addr %u Size %u", flashAddr, numBytes);
        cli_printf(CRLF);
        uint32_t i = 0;
        for(i = 0; i < numBytes; i++) {
            U32 nSourceAddress = flashAddr + i;
            U8 readVal = 0;
            STD_RESULT ret = EMEEP_Load(nSourceAddress, &readVal, 1);
            res = EHAL_RetToRes(ret);
            log_res(EEPROM_EMULATION, res, "Load");
            if(RESULT_OK==ret) {
                cli_printf("%02X", readVal);
            }
        }
        cli_printf(CRLF);


    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eer flashAddr numBytes");
    }
    return res;
}

bool eeprom_emulation_write_cli(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint32_t flashAddr = 0;
        uint8_t array[256] = {0};
        memset(array, 0xFF, sizeof(array));
        size_t numBytes = 0;
        if(res) {
            res = try_str2uint32(argv[0], &flashAddr);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "ParseErr FlashAddr %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &numBytes);
            if(false == res) {
                LOG_ERROR(EEPROM_EMULATION, "Unable to extract array %s", argv[1]);
            }
        }
        if(res) {
            LOG_INFO(EEPROM_EMULATION, "Write Addr %u Size %u", flashAddr, numBytes);
            STD_RESULT ret = EMEEP_Store((U32) flashAddr,
                                         (U8*)   array,
                                         (U32) numBytes);
            res = EHAL_RetToRes(ret);
            log_res(EEPROM_EMULATION,res,"Write");
        }
    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eew addr hex_string");
        LOG_INFO(EEPROM_EMULATION, "addr");
        LOG_INFO(EEPROM_EMULATION, "hex_string 0x[0...F]+");
    }
    return res;
}

bool eeprom_emulation_dump_cli(int32_t argc, char* argv[]) {
    bool res = false;
    U8 bankNum = 0;

    if(1<=argc) {
        res = try_str2uint8(argv[0], &bankNum);
        if(false == res) {
            LOG_ERROR(EEPROM_EMULATION, "ParseErr bankNum %s", argv[0]);
        }
    }

    if(res) {
        STD_RESULT ret = EEPROM_EMULATION_Dump(bankNum);
        res = EHAL_RetToRes(ret);
        log_res(EEPROM_EMULATION,res,"Dump");
    } else {
        LOG_ERROR(EEPROM_EMULATION, "Usage: eedu bankNum");
    }
    return res;
}






