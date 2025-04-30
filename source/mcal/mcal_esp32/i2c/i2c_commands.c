#include "i2c_commands.h"

#include <i2c.h>
#include <inttypes.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"

bool i2c_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t i2c_num = 0;
        uint8_t i2c_addr = 0;
        uint8_t array[256];
        uint32_t array_len = 0;
        if(true == res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number [1....8]");
            }
        }

        if(true == res) {
            res = try_str2uint8(argv[1], &i2c_addr);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number [1....8]");
            }
        }

        if(true == res) {
            res = try_str2array(argv[2], array, sizeof(array), &array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to extract array %s", argv[2]);
            }
        }

        if(true == res) {
            res = i2c_write(i2c_num, i2c_addr, array, array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to send I2C");
            } else {
                io_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2s instance i2c_addr hex_string");
        LOG_INFO(I2C, "instance");
        LOG_INFO(I2C, "i2c_addr");
        LOG_INFO(I2C, "hex_string 0x[0...F]+");
    }
    return res;
}

bool i2c_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}
// i2r 0 0xef 1  -- hang on
// i2r 0 0xef 2  -- hang on
bool i2c_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t i2c_num = 0;
        uint8_t i2c_addr = 0;
        uint8_t array[256];
        uint16_t array_len = 0;
        if(true == res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number [1....8]");
            }
        }

        if(true == res) {
            res = try_str2uint8(argv[1], &i2c_addr);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number [1....8]");
            }
        }

        if(true == res) {
            res = try_str2uint16(argv[2], &array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to extract array_len %s", argv[2]);
            }
        }

        if(true == res) {
            res = i2c_read(i2c_num, i2c_addr, array, array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to send I2C");
            } else {
                print_mem(array, array_len, true, false, false, true);
                io_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2r instance i2c_addr size");
        LOG_INFO(I2C, "instance");
        LOG_INFO(I2C, "i2c_addr");
        LOG_INFO(I2C, "size");
    }
    return res;
}

bool i2c_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2c_num = 0;
    uint16_t array_len = 0;
    if(0 == argc) {
        res = true;
        i2c_num = 0;
        array_len = 0;
    }
    if(1 <= argc) {
        res = true;
        if(true == res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number");
            }
        }
    }
    if(2 <= argc) {
        res = true;
        if(true == res) {
            res = try_str2uint16(argv[1], &array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse array_len");
            }
        }
    }

    if(2 < argc) {
        LOG_ERROR(I2C, "Usage: i2s instance len");
        LOG_INFO(I2C, "instance");
        res = false;
    }
    if(res) {
        uint8_t array[2] = {0xFF, 0xFF};
        memset(array, 0xFF, sizeof(array));
        uint16_t i2c_addr = 0;
        for(i2c_addr = 0; i2c_addr <= 0xFF; i2c_addr++) {
            LOG_PARN(I2C,"check 0x%02x " , i2c_addr);
            res = i2c_check_addr(i2c_num,(uint8_t)i2c_addr);
            if(false == res) {
                // LOG_ERROR(I2C, "Unable to send I2C");
            } else {
                LOG_INFO(I2C,"Spot:0x%02x " , i2c_addr);
            }
            wait_in_loop_ms(100);
        }
    }
    return res;
}
// i2cc 0xEF
// i2cc 0xaa
bool i2c_check_addr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2c_num = 0;
    if(2 == argc) {
        res = true;
        uint8_t i2c_addr = 0;
        if(true == res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C Number");
            }
        }

        if(true == res) {
            res = try_str2uint8(argv[1], &i2c_addr);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse I2C addr %s", argv[0]);
            }
        }

        if(true == res) {
            res = i2c_check_addr(i2c_num,i2c_addr);
            if(false == res) {
                LOG_ERROR(I2C, "Unknown I2C addr");
            } else {
                LOG_INFO(I2C, "addr OK!");
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2cc i2c_addr size");
        LOG_INFO(I2C, "i2c_addr");
    }
    return res;
}

bool i2c_start_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint32_t signal = 0;
        if(true == res) {
            res = try_str2uint32(argv[0], &signal);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to parse cmd %s", argv[0]);
            }
        }
        if(res) {
#if 0
            res = i2c_send_signal(signal);
            if(false==res){
                LOG_ERROR(I2C, "signal error");
            }
#endif
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2ss signal");
        LOG_INFO(I2C, "signal");
    }
    return res;
}

bool i2c_init_command(int32_t argc, char* argv[]) {
    bool res = i2c_init();
    if(false == res) {
        LOG_ERROR(I2C, "i2c_init error");
    }
    return res;
}
