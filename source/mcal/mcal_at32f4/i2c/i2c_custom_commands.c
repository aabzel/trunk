#include "i2c_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "i2c_custom_diag.h"
#include "i2c_custom_drv.h"
#include "i2c_custom_types.h"
#include "i2c_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

bool i2c_diag_custom_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = i2c_diag_custom();
    return res;
}

bool i2c_data_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t data = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &data);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr data");
        }
    }

    if(res) {
        I2cHandle_t* Node = I2cGetNode(num);
        if(Node) {
            i2c_data_send(Node->I2Cx, data);
            res = true;
        }
    }
    return res;
}

bool i2c_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
        }
    }

    if(res) {
        res = i2c_raw_reg_diag(num);
    } else {
        LOG_ERROR(I2C, "Usage i2crr Num");
    }

    return res;
}

bool i2c_all_int_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
        }
    }

    const I2cInfo_t* Info = I2cGetInfo(num);
    if(Info) {
        i2c_interrupt_enable(Info->I2Cx, I2C_ALL_INT, TRUE);
        res = true;
    } else {
        LOG_ERROR(I2C, "Usage i2cai Num");
    }

    return res;
}

// uint32_t I2cCalcArteryClkCtrlQword(double i2c_freq_hz,double apb1_freq_hz);
// i2ccd 0x40E02C2C 50000000 I2C_CLKCTRL:0x40e02c2c=Div:4,SDAD:0,scll:44, sclh:44,scld:14,
// i2ccd 0x1050589C 50000000 I2C_CLKCTRL:0x1050589c=Div:1,SDAD:0,scll:156,sclh:88,scld:5,
// i2ccd 0x1020599E 50000000 I2C_CLKCTRL:0x1020599e=Div:1,SDAD:0,scll:158,sclh:89,scld:2
// i2ccd 0x00402B4D 50000000 I2C_CLKCTRL:0x00402B4D=Div:1,Period:124 Tick,SDAD:0 Tick,scld:4 Tick,sclh:43 Tick,scll:77
// Tick
bool i2c_clkctrl_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t qword = 0;
    double base_freq_hz = 50000000.0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &qword);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C_CLKCTRL");
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &base_freq_hz);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr base_freq_hz");
        }
    }

    if(res) {
        res = i2c_clkctrl_diag(base_freq_hz, qword);
    }

    return res;
}

bool i2c_div_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t div = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Number [1-%d]", I2C_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &div);
        if(false == res) {
            LOG_ERROR(I2C, "ParseErr I2C Div");
        }
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = i2c_div_get(num, &div);
            LOG_INFO(I2C, "Get,I2C%u,Div:%u", num, div);
        } break;
        case 2: {
            LOG_INFO(I2C, "Set,I2C%u,Div:%u", num, div);
            res = i2c_div_set(num, div);

        } break;
        }

    } else {
        LOG_ERROR(I2C, "Usage i2cdi Num Div");
    }

    return res;
}
