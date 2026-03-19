#include "i2c_fsm_commands.h"

#include <inttypes.h>

#include "array_diag.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_fsm.h"
#include "i2c_mcal.h"
#include "log.h"
#include "num_to_str.h"

bool i2c_fsm_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t array[256];
        size_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1-%d]", I2C_COUNT);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2Cadd");
            }
        }

        if(res) {
            res = try_str2array(argv[2], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "Unable to extract array %s", argv[2]);
            }
        }

        if(res) {
            res = i2c_fsm_write(num, chip_addr, array, (uint16_t)array_len);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "%u SendErr Addr 0x%x Len: %u", num, chip_addr, array_len);
            } else {
                cli_printf(CRLF);
                LOG_INFO(I2C_FSM, "%u SendOk", num);
            }
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2cw Num ChipAddr HexString");
        LOG_INFO(I2C_FSM, "Num");
        LOG_INFO(I2C_FSM, "ChipAddr");
        LOG_INFO(I2C_FSM, "hex_string 0x[0...F]+");
    }
    return res;
}

bool i2c_fsm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = i2c_fsm_diag();
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2d");
    }
    return res;
}

bool i2c_fsm_empty_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "Parse,Err,I2C,Number:[1-%d]", I2C_COUNT);
        }
    }

    if(res) {
        res = i2c_fsm_empty(num);
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2cfe Num");
    }
    return res;
}

bool i2c_fsm_read_word_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t word_addr = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr Chip [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &word_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
            }
        }

        if(res) {
            LOG_INFO(I2C_FSM, "I2C%u,Chip:0x%02x,Addr:0x%02x", num, chip_addr, word_addr);
            uint16_t word = 0xFFFF;
            res = i2c_fsm_read_word(num, chip_addr, word_addr, &word);
            if(res) {
#ifdef HAS_BIN_2_STR
                LOG_INFO(I2C_FSM, "Word[%u]=0x%04X=0b%s", word_addr, word, utoa_bin16(word));
#endif
                cli_printf(CRLF);
            } else {
                LOG_ERROR(I2C_FSM, "ReadError");
            }
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2crd I2cNum ChipAddr WordAddr");
    }
    return res;
}

bool i2c_fsm_read_byte_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t reg_addr = 0;
        uint8_t value[2] = {0xFF};
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &reg_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
            }
        }

        if(res) {
            LOG_INFO(I2C_FSM, "I2C%u,Chip:0x%02x,Addr:0x%02x", num, chip_addr, reg_addr);
            res = i2c_fsm_read_byte(num, chip_addr, reg_addr, value);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "Unable to send I2C");
            } else {
#ifdef HAS_BIN_2_STR
                LOG_INFO(I2C_FSM, "Reg[%u]=0x%02x=0b%s", reg_addr, value[0], utoa_bin8(value[0]));
                cli_printf(CRLF);
#endif
            }
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2crr I2cNum ChipAddr RegAddr");
        LOG_INFO(I2C_FSM, "I2cNum");
        LOG_INFO(I2C_FSM, "ChipAddr");
        LOG_INFO(I2C_FSM, "RegAddr");
    }
    return res;
}

// i2r 0 0xef 1  -- hang on
// i2r 0 0xef 2  -- hang on
bool i2c_fsm_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        static uint8_t array[256];
        uint16_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint16(argv[2], &array_len);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "Unable to extract array_len %s", argv[2]);
            }
        }

        if(res) {
            res = i2c_fsm_read(num, chip_addr, array, array_len);
            if(false == res) {
                LOG_ERROR(I2C_FSM, "Unable to send I2C");
            } else {
#ifdef HAS_ARRAY_DIAG
                res = print_mem(array, array_len, true, false, true, false);
#endif
                cli_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2cr Num ChipAddr Size");
        LOG_INFO(I2C_FSM, "Num");
        LOG_INFO(I2C_FSM, "ChipAddr");
        LOG_INFO(I2C_FSM, "Size");
    }
    return res;
}

// i2cc 2 0x1A
bool i2c_fsm_scan_base_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    if(0 == argc) {
        res = true;
        LOG_ERROR(I2C_FSM, "ParseErr I2C Number");
    }

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number");
        }
    }

    if(res) {
        LOG_INFO(I2C_FSM, "I2C%u", num);
        if(0 == argc) {
            num = 0;
            uint32_t cnt = i2c_get_cnt();
            for(num = 0; num <= cnt; num++) {
                I2cHandle_t* Node = I2cGetNode(num);
                if(Node) {
                    res = i2c_fsm_scan_base_diag(num);
                    if(res) {
                        LOG_INFO(I2C_FSM, "%u ScanOk", num);
                    } else {
                        LOG_ERROR(I2C_FSM, "%u ScanErr", num);
                    }
                }
            }
        } else {
            res = i2c_fsm_scan_base_diag(num);
            if(res) {
                LOG_INFO(I2C_FSM, "%u ScanOk", num);
            } else {
                LOG_ERROR(I2C_FSM, "%u ScanErr", num);
            }
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2cfsb Num");
        res = false;
    }
    return res;
}
//
// i2cc 2 0x1A
bool i2c_fsm_check_addr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t chip_addr = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C addr %s", argv[1]);
        }
    }

    if(res) {
        res = i2c_fsm_check_addr(num, chip_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "%u Unknown I2C addr 0x%02x", num, chip_addr);
        } else {
            LOG_INFO(I2C_FSM, "%u addr 0x%02x Exist", num, chip_addr);
        }

    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2cs I2cNum I2cAddr");
        LOG_INFO(I2C_FSM, "chip_addr");
    }
    return res;
}

bool i2c_fsm_init_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2cNumber");
        }
    }
    if(res) {
        res = i2c_fsm_init_one(num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "I2cInitErr %u", num);
        }
    }
    return res;
}

/* i2crm 2 0x35 0x3E 2*/
bool i2c_fsm_read_memory_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint32_t size = 2;
    static uint8_t buff[10] = {0};
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
        }
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &size);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr size");
        }
    }

    if(res) {
        LOG_INFO(I2C_FSM, "I2C%u,Chip:0x%02x,Reg:0x%02x,Size:%u", num, chip_addr, reg_addr, size);
        res = i2c_fsm_read_mem(num, chip_addr, &reg_addr, 1, buff, size);
        if(res) {
            LOG_INFO(I2C_FSM, "Read,Mem,Ok");
#ifdef HAS_ARRAY_DIAG
            print_mem(buff, size, true, true, true, true);
            cli_printf(CRLF);
#endif // HAS_ARRAY_DIAG
        } else {
            LOG_ERROR(I2C_FSM, "Read,Mem,Err");
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2crm I2cNum ChipAddr RegAddr Size");
        LOG_INFO(I2C_FSM, "I2cNum");
        LOG_INFO(I2C_FSM, "ChipAddr");
        LOG_INFO(I2C_FSM, "RegAddr");
    }
    return res;
}

bool i2c_fsm_write_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[3], &value);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
        }
    }

    if(res) {
        res = i2c_fsm_write_byte(num, chip_addr, reg_addr, value);
        if(res) {
            LOG_INFO(I2C_FSM, "RegWriteOk");
            cli_printf(CRLF);
        } else {
            LOG_ERROR(I2C_FSM, "RegWriteErr");
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2crw I2cNum ChipAddr RegAddr Value");
    }
    return res;
}

bool i2c_fsm_write_reg_verify_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[3], &value);
        if(false == res) {
            LOG_ERROR(I2C_FSM, "ParseErr RegAddr");
        }
    }

    if(res) {
        res = i2c_fsm_write_byte_verify(num, chip_addr, reg_addr, value);
        if(res) {
            LOG_INFO(I2C_FSM, "RegWriteVerifyOk");
            cli_printf(CRLF);
        } else {
            LOG_ERROR(I2C_FSM, "RegWriteVerifyErr");
        }
    } else {
        LOG_ERROR(I2C_FSM, "Usage: i2crwv I2cNum ChipAddr RegAddr Value");
    }
    return res;
}
