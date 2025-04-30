#include "i2c_commands.h"

#include <inttypes.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_mcal.h"
#include "num_to_str.h"

#ifdef HAS_MCAL_CUSTOM
#include "i2c_custom_diag.h"
#include "i2c_custom_types.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TIME
#include "none_blocking_pause.h"
#endif

bool i2c_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t array[256] = {0};
        uint32_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2Cadd");
            }
        }

        if(res) {
            res = try_str2array(argv[2], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to extract array %s", argv[2]);
            }
        }

        if(res) {
            res = i2c_api_write(num, chip_addr, array, (uint16_t)array_len);
            if(false == res) {
                LOG_ERROR(I2C, "%u SendErr Addr 0x%x Len: %u", num, chip_addr, array_len);
            } else {
                cli_printf(CRLF);
                LOG_INFO(I2C, "%u SendOk", num);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2cw Num ChipAddr HexString");
        LOG_INFO(I2C, "Num");
        LOG_INFO(I2C, "ChipAddr");
        LOG_INFO(I2C, "hex_string 0x[0...F]+");
    }
    return res;
}

bool i2c_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
#ifdef HAS_I2C_DIAG
        res = i2c_diag();
#endif
    } else {
        LOG_ERROR(I2C, "Usage: i2d");
    }
    return res;
}

bool i2c_read_word_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t word_addr = 0;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr Chip [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &word_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr RegAddr");
            }
        }

        if(res) {
            LOG_INFO(I2C, "I2C%u,Chip:0x%02x,Addr:0x%02x", num, chip_addr, word_addr);
            uint16_t word = 0xFFFF;
            res = i2c_api_read_word(num, chip_addr, word_addr, &word);
            if(res) {
                LOG_INFO(I2C, "Word[%u]=0x%04X=0b%s", word_addr, word, utoa_bin16(word));
                cli_printf(CRLF);
            } else {
                LOG_ERROR(I2C, "ReadError");
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2crd I2cNum ChipAddr WordAddr");
    }
    return res;
}

bool i2c_read_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t num = 0;
        uint8_t chip_addr = 0;
        uint8_t reg_addr = 0;
        static uint8_t value[2] = {0xFF};
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &reg_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr RegAddr");
            }
        }

        if(res) {
            LOG_INFO(I2C, "I2C%u,Chip:0x%02x,Addr:0x%02x", num, chip_addr, reg_addr);
            res = i2c_api_read_byte(num, chip_addr, reg_addr, value);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to send I2C");
            } else {
                LOG_INFO(I2C, "Reg[%u]=0x%02x=0b%s", reg_addr, value[0], utoa_bin8(value[0]));
                cli_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2crr I2cNum ChipAddr RegAddr");
        LOG_INFO(I2C, "I2cNum");
        LOG_INFO(I2C, "ChipAddr");
        LOG_INFO(I2C, "RegAddr");
    }
    return res;
}

// i2r 0 0xef 1  -- hang on
// i2r 0 0xef 2  -- hang on
bool i2c_read_command(int32_t argc, char* argv[]) {
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
                LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &chip_addr);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint16(argv[2], &array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to extract array_len %s", argv[2]);
            }
        }

        if(res) {
            res = i2c_api_read(num, chip_addr, array, array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to send I2C");
            } else {
#ifdef HAS_ARRAY_DIAG
                res = print_mem(array, array_len, true, false, true, false);
                cli_printf(CRLF);
#endif
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2cr Num ChipAddr Size");
        LOG_INFO(I2C, "Num");
        LOG_INFO(I2C, "ChipAddr");
        LOG_INFO(I2C, "Size");
    }
    return res;
}

// i2cc 2 0x1A
bool i2c_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    if(0 == argc) {
        res = true;
        LOG_ERROR(I2C, "ParseErr I2C Number");
    }

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(res) {
        LOG_INFO(I2C, "I2C%u", num);
        if(0 == argc) {
            num = 0;
            uint32_t cnt = i2c_get_cnt();
            for(num = 0; num <= cnt; num++) {
                I2cHandle_t* Node = I2cGetNode(num);
                if(Node) {
#ifdef HAS_I2C_DIAG
                    res = i2c_scan_diag(num);
                    if(res) {
                        LOG_INFO(I2C, "%u ScanOk", num);
                    } else {
                        LOG_ERROR(I2C, "%u ScanErr", num);
                    }
#endif
                }
            }
        } else {
#ifdef HAS_I2C_DIAG
            res = i2c_scan_diag(num);
#endif
            if(res) {
                LOG_INFO(I2C, "%u ScanOk", num);
            } else {
                LOG_ERROR(I2C, "%u ScanErr", num);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2cs Num");
        LOG_INFO(I2C, "Num");
        res = false;
    }
    return res;
}
//
// i2cc 2 0x1A
bool i2c_check_addr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t chip_addr = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C addr %s", argv[1]);
        }
    }

    if(res) {
        res = i2c_check_addr(num, chip_addr);
        if(false == res) {
            LOG_ERROR(I2C, "%u Unknown I2C addr 0x%02x", num, chip_addr);
        } else {
            LOG_INFO(I2C, "%u addr 0x%02x Exist", num, chip_addr);
        }

    } else {
        LOG_ERROR(I2C, "Usage: i2cs I2cNum I2cAddr");
        LOG_INFO(I2C, "chip_addr");
    }
    return res;
}

bool i2c_start_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t signal = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &signal);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr cmd %s", argv[1]);
        }
    }
    if(res) {
        res = i2c_send_signal(num, (I2cSignal_t)signal);
        if(res) {
            LOG_INFO(I2C, "I2C%u" LOG_OK, num);
        } else {
            LOG_ERROR(I2C, "I2C%u SignalErr", num);
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2ss num signal");
        LOG_INFO(I2C, "%u-Statr %u-Stop", I2C_START, I2C_STOP);
    }
    return res;
}

bool i2c_init_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2cNumber");
        }
    }
    if(res) {
        res = i2c_init_one(num);
        if(false == res) {
            LOG_ERROR(I2C, "I2cInitErr %u", num);
        }
    }
    return res;
}

/* i2crm 2 0x35 0x3E 2*/
bool i2c_read_memory_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint32_t size = 2;
    static uint8_t buff[10] = {0};
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr RegAddr");
        }
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &size);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr size");
        }
    }

    if(res) {
        LOG_INFO(I2C, "I2C%u,Chip:0x%02x,Reg:0x%02x,Size:%u", num, chip_addr, reg_addr, size);
        res = i2c_api_read_mem(num, chip_addr, &reg_addr, 1, buff, size);
        if(res) {
            LOG_INFO(I2C, "RegMemOk");
#ifdef HAS_ARRAY_DIAG
            print_mem(buff, size, true, true, true, true);
            cli_printf(CRLF);
#endif
        } else {
            LOG_ERROR(I2C, "ReadMemErr");
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2crm I2cNum ChipAddr RegAddr Size");
        LOG_INFO(I2C, "I2cNum");
        LOG_INFO(I2C, "ChipAddr");
        LOG_INFO(I2C, "RegAddr");
    }
    return res;
}

bool i2c_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr RegAddr");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[3], &value);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr RegAddr");
        }
    }

    if(res) {
        res = i2c_api_reg_write(num, chip_addr, reg_addr, value);
        if(res) {
            LOG_INFO(I2C, "RegWriteOk");
            cli_printf(CRLF);
        } else {
            LOG_ERROR(I2C, "RegWriteErr");
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2crw I2cNum ChipAddr RegAddr Value");
    }
    return res;
}

bool i2c_reg_write_verify_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t chip_addr = 0;
    uint8_t reg_addr = 0x2E;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &chip_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &reg_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr RegAddr");
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[3], &value);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr RegAddr");
        }
    }

    if(res) {
        res = i2c_api_reg_write_verify(num, chip_addr, reg_addr, value);
        if(res) {
            LOG_INFO(I2C, "RegWriteVerifyOk");
            cli_printf(CRLF);
        } else {
            LOG_ERROR(I2C, "RegWriteVerifyErr");
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2crwv I2cNum ChipAddr RegAddr Value");
    }
    return res;
}
