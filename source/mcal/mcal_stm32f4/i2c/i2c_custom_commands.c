#include "i2c_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_mcal.h"
#include "i2c_custom_diag.h"
#include "i2c_custom_types.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"
#if 0

bool i2c_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(3 == argc) {
        res = true;
        uint8_t i2c_num = 0;
        uint8_t i2c_addr = 0;
        uint8_t array[256];
        uint32_t array_len = 0;
        if(res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &i2c_addr);
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
            res = i2c_write(i2c_num, i2c_addr, array, (uint16_t)array_len);
            if(false == res) {
                LOG_ERROR(I2C, "%u SendErr Addr 0x%x Len: %u", i2c_num, i2c_addr, array_len);
            } else {
                cli_printf(CRLF);
                LOG_INFO(I2C, "%u SendOk", i2c_num);
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

static bool i2c_diag_low_level(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},    {5, "sta"}, {6, "Mode"}, {5, "ErrIt"}, {5, "EntIt"}, {5, "BufIt"},
        {5, "DmaIt"}, {5, "MHz"}, {5, "role"}, {5, "state"}, {5, "dir"},
    };

    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint8_t i2c_num = 0;
    char temp_str[120] = "";
    for(i2c_num = 1; i2c_num <= I2C_COUNT; i2c_num++) {
        I2C_TypeDef* I2Cx = i2c_get_instance(i2c_num);
        if(I2Cx) {
            I2cRegControl1_t RegControl1;
            RegControl1.reg_val = I2Cx->CR1;
            I2cRegControl2_t RegControl2;
            RegControl2.reg_val = I2Cx->CR2;
            I2cRegStatus2_t RegStatus2;
            RegStatus2.reg_val = I2Cx->SR2;
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegControl1.pe));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, I2cMode2Str(RegControl1.sm_bus));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegControl2.iterr_en));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegControl2.itevt_en));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegControl2.itbuf_en));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOff2Str(RegControl2.dma_en));

            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2cBusRole2Str(RegStatus2.msl));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2cBusState2Str(RegStatus2.busy));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2cDir2Str(RegStatus2.tra));

            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, RegControl2.freq);
            cli_printf(TSEP " %3u ", i2c_num);
            cli_printf("%s" CRLF, temp_str);
        }
    }

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

static bool i2c_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {5, "I2C"}, {7, "ErrCnt"}, {14, "State"}, {17, "name"}};
    uint16_t num = 1;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for(i = 1; i <= I2C_COUNT; i++) {
        I2cHandle_t* I2cNode = i2c_get_int_node(i);
        if(I2cNode) {
            const I2cConfig_t* I2cConfNode = i2c_get_conf_node(i);
            if(I2cConfNode) {
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, (unsigned int)i);
                snprintf(temp_str, sizeof(temp_str), "%s  %3u  " TSEP, temp_str, (unsigned int)I2cNode->error_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s  %12s  " TSEP, temp_str,
                         I2cHalState2Str(I2cNode->i2c_h.State));
                snprintf(temp_str, sizeof(temp_str), "%s  %15s  " TSEP, temp_str, I2cConfNode->name);
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, temp_str);
            }
            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2c_diag_low_level();
    } else {
        LOG_ERROR(I2C, "Usage: i2dl");
    }
    return res;
}

bool i2c_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = i2c_diag();
    } else {
        LOG_ERROR(I2C, "Usage: i2d");
    }
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
        if(res) {
            res = try_str2uint8(argv[0], &i2c_num);
            if(false == res) {
                LOG_ERROR(I2C, "ParseErr I2C Number [1....8]");
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &i2c_addr);
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
            res = i2c_read(i2c_num, i2c_addr, array, array_len);
            if(false == res) {
                LOG_ERROR(I2C, "Unable to send I2C");
            } else {
                res = print_mem(array, array_len, true, false, true, false);
                cli_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2cr instance i2c_addr size");
        LOG_INFO(I2C, "instance");
        LOG_INFO(I2C, "i2c_addr");
        LOG_INFO(I2C, "size");
    }
    return res;
}

static bool i2c_scan_diag(uint8_t i2c_num) {
    bool res = false;
    LOG_INFO(I2C, "InterfaceNum %u", i2c_num);
    static const table_col_t cols[] = {
        {4, "--"}, {4, "x0"}, {4, "x1"}, {4, "x2"}, {4, "x3"}, {4, "x4"}, {4, "x5"}, {4, "x6"}, {4, "x7"},
        {4, "x8"}, {4, "x9"}, {4, "xA"}, {4, "xB"}, {4, "xC"}, {4, "xD"}, {4, "xE"}, {4, "xF"},
    };
    Type8Union_t un8;
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    uint8_t l = 0, h = 0;
    bool lres = false;
    for(h = 0; h <= 0xF; h++) {
        un8.nibble_h = h;
        cli_printf(TSEP);
        cli_printf(" %xx " TSEP, h);
        for(l = 0; l <= 0xF; l++) {
            un8.nibble_h = h;
            un8.nibble_l = l;
            lres = i2c_check_addr(i2c_num, un8.u8);
            if(lres) {
                cli_printf(" %02x " TSEP, un8.u8);
                res = true;
            } else {
                cli_printf(" -- " TSEP);
            }
            wait_in_loop_ms(5);
        }
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_scan_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2c_num = 1;
    if(0 == argc) {
        res = true;
    }
    if(1 == argc) {
        res = try_str2uint8(argv[0], &i2c_num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(res) {
        if(0 == argc) {
            i2c_num = 0;
            for(i2c_num = 0; i2c_num < i2c_get_cnt(); i2c_num++) {
                I2cHandle_t* I2cNode = i2c_get_int_node(i2c_num);
                if(I2cNode) {
                    res = i2c_scan_diag(i2c_num);
                }
            }
        } else {
            res = i2c_scan_diag(i2c_num);
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2s instance");
        LOG_INFO(I2C, "instance");
        res = false;
    }
    return res;
}
// i2cc 0xEF
// i2cc 0xaa
bool i2c_check_addr_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i2c_addr = 0;
    uint8_t i2c_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2c_num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &i2c_addr);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C addr %s", argv[0]);
        }

        if(res) {
            res = i2c_check_addr(i2c_num, i2c_addr);
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
    uint8_t signal = 0;
    uint8_t i2c_num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2c_num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number");
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &signal);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr cmd %s", argv[0]);
        }
    }
    if(res) {
        res = i2c_send_signal(i2c_num, (I2cSignal_t)signal);
        if(false == res) {
            LOG_ERROR(I2C, "%u Err", i2c_num);
        } else {
            LOG_INFO(I2C, "%u" LOG_OK, i2c_num);
        }
    } else {
        LOG_ERROR(I2C, "Usage: i2ss i2c_num signal");
        LOG_INFO(I2C, "%u-Statr %u-Stop", I2C_START, I2C_STOP);
    }
    return res;
}

bool i2c_init_command(int32_t argc, char* argv[]) {
    uint8_t i2c_num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &i2c_num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2cNumber");
        }
    }
    if(res) {
        res = i2c_init_ll(i2c_num);
        if(false == res) {
            LOG_ERROR(I2C, "I2cInitErr %u", i2c_num);
        }
    }
    return res;
}
#endif
