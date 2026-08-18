#include "sa51034_drv.h"

#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "bit_const.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

Sa51GainCode_t Sa51GainToCode(Gain_t gain_db) {
    Sa51GainCode_t code = SA51_GAIN_CODE_20_DB;
    switch((uint8_t)gain_db) {
    case 20:
        code = SA51_GAIN_CODE_20_DB;
        break;
    case 26:
        code = SA51_GAIN_CODE_26_DB;
        break;
    case 32:
        code = SA51_GAIN_CODE_32_DB;
        break;
    case 36:
        code = SA51_GAIN_CODE_36_DB;
        break;
    }
    return code;
}

Sa51SwFrequency_t Sa51FrequencyToCode(uint32_t frequency_hz) {
    Sa51SwFrequency_t code = SA51_SW_FREQ_400KHZ;
    switch(frequency_hz) {
    case 400000:
        code = SA51_SW_FREQ_400KHZ;
        break;
    case 500000:
        code = SA51_SW_FREQ_500KHZ;
        break;
    }
    return code;
    Sa51FrequencyToCode;
}

Gain_t Sa51GainCodeToGain(Sa51GainCode_t g_code) {
    Gain_t gain = 0;
    switch((uint8_t)g_code) {
    case SA51_GAIN_CODE_20_DB:
        gain = 20;
        break;
    case SA51_GAIN_CODE_26_DB:
        gain = 26;
        break;
    case SA51_GAIN_CODE_32_DB:
        gain = 32;
        break;
    case SA51_GAIN_CODE_36_DB:
        gain = 36;
        break;
    }
    return gain;
}

uint32_t Sa51FrequencyCodeToHz(Sa51SwFrequency_t f_code) {
    uint32_t frequency_hz = 0.0;
    switch((uint8_t)f_code) {
    case SA51_SW_FREQ_400KHZ:
        frequency_hz = 400000;
        break;
    case SA51_SW_FREQ_500KHZ:
        frequency_hz = 500000;
        break;
    }
    return frequency_hz;
}

COMPONENT_GET_NODE(Sa51034, sa51034)
COMPONENT_GET_CONFIG(Sa51034, sa51034)

const Sa51034RegInfo_t Sa51RegInfo[] = {
    {
        .valid = true,
        .addr = SA51034_REG_LATCHED_FAULT,
        .name = "LatchedFAULT",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = SA51034_REG_STATUS_AND_LOAD_DIAGNOSTIC,
        .name = "StatusAndLoadDiagnostic",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = SA51034_REG_CONTROL,
        .name = "Control",
        .access = ACCESS_READ_WRITE,
    },
};

uint32_t sa51034_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(Sa51RegInfo);
    return cnt;
}

static const Sa51034PowerLimitInfo_t PowerLimitInfo[] = {
    {
        .code = SA51_POWER_LIMIT_DISABLE,
        .power_limit_v = 99.9,
    },
    {
        .code = SA51_POWER_LIMIT_11_5_V,
        .power_limit_v = 11.5,
    },
    {
        .code = SA51_POWER_LIMIT_9_6_V,
        .power_limit_v = 9.6,
    },
    {
        .code = SA51_POWER_LIMIT_7_5_V,
        .power_limit_v = 7.5,
    },
    {
        .code = SA51_POWER_LIMIT_6_1_V,
        .power_limit_v = 6.1,
    },
    {
        .code = SA51_POWER_LIMIT_4_9_V,
        .power_limit_v = 4.9,
    },
    {
        .code = SA51_POWER_LIMIT_4_2_V,
        .power_limit_v = 4.2,
    },
    {
        .code = SA51_POWER_LIMIT_3_4_V,
        .power_limit_v = 3.4,
    },
};

double Sa51PowerLimitCodeToVolts(Sa51PowerLimit_t pl_code) {
    double power_limit_v = 99.9;

    uint32_t cnt = ARRAY_SIZE(PowerLimitInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(PowerLimitInfo[i].code == pl_code) {
            power_limit_v = PowerLimitInfo[i].power_limit_v;
        }
    }

    return power_limit_v;
}

Sa51PowerLimit_t Sa51PowerLimitToCode(double power_limit_v) {
    bool res = false;

    uint32_t cnt = ARRAY_SIZE(PowerLimitInfo);
    uint32_t i = 0;
    Sa51034PowerLimitItem_t Cur;
    Sa51034PowerLimitItem_t Best;

    Best.diff_v = 9999.9;
    Best.code = SA51_POWER_LIMIT_DISABLE;
    Best.power_limit_v = 99.9;
    for(i = 0; i < cnt; i++) {
        Cur.code = PowerLimitInfo[i].code;
        Cur.power_limit_v = PowerLimitInfo[i].power_limit_v;
        Cur.diff_v = fabs(PowerLimitInfo[i].power_limit_v - power_limit_v);
        if(Cur.diff_v < Best.diff_v) {
            memcpy(&Best, &Cur, sizeof(Sa51034PowerLimitItem_t));
            res = true;
        }
    }
    LOG_INFO(SA51034, "Code:%u=PowerLimit:%f V,%u", Best.code, Best.power_limit_v, res);
    return Best.code;
}

bool sa51034_reg_read_ll(Sa51034Handle_t* Node, Sa51034RegAddr_t addr, uint8_t* const byte) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(SA51034, "Read Chip:0x%x,Reg:0x%02x", Node->chip_addr, addr);
#ifdef HAS_I2C
        uint8_t addr_val = (uint8_t)addr;
        uint8_t reg_byte = 0;
        LOG_DEBUG(SA51034, "Addr:0x%02x,AddrVal:0x%02x", addr, addr_val);
        res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, &addr_val, 1, (uint8_t*)&reg_byte, 1);
        if(res) {
            *byte = reg_byte;
            LOG_PARN(SA51034, "ReadMemOk,Reg:0x%02x,Val:0x%02x", addr, reg_byte);
        } else {
            LOG_ERROR(SA51034, "I2C%u,ReadMemErr,Reg:0x%02x=%s", Node->i2c_num, addr, Sa51034RegAddrToName(addr));
        }
#endif /*HAS_I2C*/
    }
    return res;
}

bool sa51034_reg_read_all(uint8_t num) {
    bool res = false;
    const Sa51034Config_t* Config = Sa51034GetConfig(num);
    if(Config) {
        uint8_t i = 0;
        uint8_t ok_cnt = 0;
        for(i = 0; i < SA51034_REG_CNT; i++) {
            // res = sa51034_reg_read(Sa51034RegVal[i].addr, &Sa51034RegVal[i].value.byte);
            if(res) {
                ok_cnt++;
            } else {
                // LOG_ERROR(I2C, "Read Reg:0x%02x Err", Sa51034RegVal[i].addr);
            }
        }

        if(ok_cnt == SA51034_REG_CNT) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool sa51034_is_connected_ll(Sa51034Handle_t* Node) {
    bool res = true;
    /*TODO*/
    return res;
}

bool sa51034_is_connected(uint8_t num) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_is_connected_ll(Node);
    }
    return res;
}

bool sa51034_reg_write_ll(Sa51034Handle_t* Node, Sa51034RegAddr_t addr, uint8_t byte) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(SA51034, "Set Reg:0x%02x=%s,Val:0x%02x", addr, Sa51034RegAddrToName(addr), byte);
#ifdef HAS_I2C
        uint8_t buff[2] = {addr, byte};
        res = i2c_api_write(Node->i2c_num, Node->chip_addr, buff, 2);
        if(res) {
            LOG_DEBUG(SA51034, "WriteOk!Addr:0x%02x,Val:0x%s", addr, ArrayToStr(buff, 2));
        } else {
            LOG_ERROR(SA51034, "WriteErr,Addr:0x%02x=%s,Val:0x%04x", addr, Sa51034RegAddrToName(addr), byte);
        }
#endif /*HAS_I2C*/
    } else {
    }
    return res;
}

/*Figure 9. Writing One Byte of Data to the SA51034*/
bool sa51034_reg_write(uint8_t num, Sa51034RegAddr_t addr, uint8_t byte) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_write_ll(Node, addr, byte);
    } else {
        LOG_ERROR(SA51034, "%u", num);
    }
    return res;
}

bool sa51034_reg_write_verify(uint8_t num, Sa51034RegAddr_t addr, uint8_t set_byte) {
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(SA51034, "SetVerify Reg:0x%02x Val:0x%02x", addr, set_byte);
    res = sa51034_reg_write(num, addr, set_byte);
    if(res) {
        uint8_t byte_read = 0;
        res = sa51034_reg_read(num, addr, &byte_read);
        if(byte_read == set_byte) {
            res = true;
            LOG_INFO(SA51034, "SetVerifyReg:0x%02x Val:0x%02x Ok", addr, set_byte);
        } else {
            LOG_ERROR(SA51034, "VerifyErrReg:0x%02x Set:0x%02x != Get:0x%02x", addr, set_byte, byte_read);
            res = false;
        }
    }

    return res;
}

bool sa51034_reset(uint8_t num) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        LOG_WARNING(SA51034, "PowerReset,%s,Active:%s", GpioPadToStr(Node->power_enable),
                    GpioLevel2Str(Node->power_active_level));
        GpioLogicLevel_t passiv = gpio_opposite_level_get(Node->power_active_level);
        res = gpio_set_logic_level(Node->power_enable.byte, passiv);
        if(res) {
            res = wait_in_loop_ms(500);
            res = gpio_set_logic_level(Node->power_enable.byte, Node->power_active_level);
        }
    }
    return res;
}

bool sa51034_is_valid_addr(uint8_t addr) {
    bool res = false;
    const Sa51034RegInfo_t* Node = Sa51034RegAddrToInfo(addr);
    if(Node) {
        res = true;
    }

    return res;
}

bool sa51034_reg_read(uint8_t num, Sa51034RegAddr_t addr, uint8_t* const byte) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        LOG_DEBUG(SA51034, "Read Chip:0x%x,Reg:0x%02x", Node->chip_addr, addr);
        res = sa51034_reg_read_ll(Node, addr, byte);
        if(res) {
            LOG_PARN(SA51034, "ReadOk,Reg:0x%02x,Val:0x%02x", addr, *byte);
        } else {
            LOG_ERROR(SA51034, "ReadErr,Reg:0x%02x=%s", addr, Sa51034RegAddrToName(addr));
        }
    }
    return res;
}

bool sa51034_init_custom(void) {
    log_level_get_set(SA51034, LOG_LEVEL_INFO);
    return true;
}

static bool sa51034_register_config(uint8_t num, const Sa51034RegVal_t* const Reg, uint32_t cnt) {
    bool res = false;
    if(Reg) {
        if(cnt) {
            uint32_t i = 0;
            uint32_t ok = 0;
            for(i = 0; i < cnt; i++) {
                res = sa51034_reg_write(num, Reg[i].addr, Reg[i].Reg.byte);
                if(res) {
                    ok++;
                }
            }

            if(ok == cnt) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

static bool sa51034_init_common(const Sa51034Config_t* const Config, Sa51034Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->chip_addr = Config->chip_addr;
            Node->fault_z = Config->fault_z;
            Node->frequency_hz = Config->frequency_hz;
            Node->gain = Config->gain;
            Node->i2c_num = Config->i2c_num;
            Node->mute = Config->mute;
            Node->power_active_level = Config->power_active_level;
            Node->power_enable = Config->power_enable;
            Node->power_limit = Config->power_limit;
            Node->num = Config->num;
            Node->shutdown = Config->shutdown;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool sa51034_init_one(uint8_t num) {
    bool res = false;
    const Sa51034Config_t* Config = Sa51034GetConfig(num);
    if(Config) {
        LOG_WARNING(SA51034, "Init:%s", Sa51034ConfigToStr(Config));
        Sa51034Handle_t* Node = Sa51034GetNode(num);
        if(Node) {
            res = sa51034_init_common(Config, Node);

            res = gpio_set_logic_level(Node->power_enable.byte, Node->power_active_level);

            log_level_get_set(I2C, LOG_LEVEL_DEBUG);
            log_level_get_set(SA51034, LOG_LEVEL_DEBUG);

            res = sa51034_is_connected_ll(Node);
            if(res) {
                res = sa51034_register_config(num, Config->RegVals, Config->reg_val_cnt);
            } else {
                LOG_ERROR(SA51034, "LinkErr");
            }

            log_level_get_set(I2C, LOG_LEVEL_INFO);
            log_level_get_set(SA51034, LOG_LEVEL_NOTICE);
        } else {
            LOG_ERROR(SA51034, "NodeErr");
        }
    }
    return res;
}

const Sa51034RegInfo_t* Sa51034RegAddrToInfo(Sa51034RegAddr_t addr) {
    Sa51034RegInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(Sa51RegInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(Sa51RegInfo[i].valid) {
            if(addr == Sa51RegInfo[i].addr) {
                Info = &Sa51RegInfo[i];
            }
        }
    }
    return Info;
}

static bool sa51_proc_status_and_load_diagnostic(Sa51034RegStatusAndLoadDiagnostic_t* Node) {
    bool res = true;
    if(Node) {
        if(Node->fault_state) {
            res = false;
            LOG_ERROR(SA51034, "Fault!");
        }
        if(Node->short_pvdd) {
            res = false;
            LOG_ERROR(SA51034, "ShortPVDD");
        }
        if(Node->short_gnd) {
            res = false;
            LOG_ERROR(SA51034, "ShortGND");
        }

        if(Node->open_load) {
            res = false;
            LOG_WARNING(SA51034, "OpenLoad");
        }

        if(Node->shorted_load) {
            res = false;
            LOG_ERROR(SA51034, "ShortedLoad");
        }
        if(Node->mute) {

            LOG_DEBUG(SA51034, "mute");
        }
        if(Node->play) {

            LOG_DEBUG(SA51034, "play");
        }
        if(Node->run_load_detect) {

            LOG_DEBUG(SA51034, "LoadDetectRun");
        }
    }
    return res;
}

static bool sa51_proc_latched_fault(Sa51034RegLatchedFault_t* Node) {
    bool res = true;
    if(Node) {
        if(Node->ld_fault) {
            res = false;
            LOG_ERROR(SA51034, "LoadDiagnosticsFault!");
        }

        if(Node->over_current_shutdown) {
            res = false;
            LOG_ERROR(SA51034, "OverCurrentShutdown");
        }

        if(Node->pvdd_under_voltage) {
            res = false;
            LOG_ERROR(SA51034, "PVddUnderVoltage");
        }

        if(Node->pvdd_over_voltage) {
            res = false;
            LOG_ERROR(SA51034, "PVddOverVoltage");
        }

        if(Node->dc_offset_protection) {

            LOG_DEBUG(SA51034, "DcOffSetPprotection");
        }

        if(Node->over_temperature_shutdown) {

            LOG_DEBUG(SA51034, "OverTemperatureShutdown");
        }
    }
    return res;
}

bool sa51034_is_fault_ll(Sa51034Handle_t* Node) {
    bool res = false;
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    res = gpio_get_state(Node->fault_z.byte, &logic_level);
    if(res) {
        if(GPIO_LVL_LOW == logic_level) {
            LOG_ERROR(SA51034, "GPIO,FAULTZ!");
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool sa51034_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(SA51034, "Proc:%u", num);
    const Sa51034Config_t* Config = Sa51034GetConfig(num);
    if(Config) {
        Sa51034Handle_t* Node = Sa51034GetNode(num);
        if(Node) {
            res = sa51034_is_connected_ll(Node);
            if(res) {
                LOG_DEBUG(SA51034, "%u I2cLinkOk", num);

                res = sa51034_reg_read_ll(Node, SA51034_REG_LATCHED_FAULT, &Node->LatchedFault.byte);
                if(res) {
                    LOG_DEBUG(SA51034, "LatchedFault:0x%x", Node->LatchedFault.byte);
                }

                res = sa51034_reg_read_ll(Node, SA51034_REG_STATUS_AND_LOAD_DIAGNOSTIC,
                                          &Node->StatusAndLoadDiagnostic.byte);
                if(res) {
                    LOG_DEBUG(SA51034, "StatusAndLoadDiagnostic:%u", Node->StatusAndLoadDiagnostic.byte);
                }

                res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
                if(res) {
                    LOG_DEBUG(SA51034, "Control:%u", Node->ControlRegister.byte);
                }

                res = sa51_proc_status_and_load_diagnostic(&Node->StatusAndLoadDiagnostic);
                res = sa51_proc_latched_fault(&Node->LatchedFault);

                res = sa51034_is_fault_ll(Node);
                if(res) {
                    LOG_ERROR(SA51034, "FAULTZ!");
                }

            } else {
                LOG_WARNING(SA51034, "%u I2cLinkErr", num);
            }
        } else {
            LOG_ERROR(SA51034, "NodeErr %u", num);
        }
    }
    return res;
}

bool sa51034_gain_get(uint8_t num, Gain_t* const gain_db) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            *gain_db = Sa51GainCodeToGain(Node->ControlRegister.gain);
        }
    }
    return res;
}

bool sa51034_frequency_get(uint8_t num, uint32_t* const frequency_hz) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            *frequency_hz = Sa51FrequencyCodeToHz(Node->ControlRegister.frequency);
        }
    }
    return res;
}

bool sa51034_frequency_set(uint8_t num, uint32_t frequency_hz) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            Node->ControlRegister.frequency = Sa51FrequencyToCode(frequency_hz);
            res = sa51034_reg_write_ll(Node, SA51034_REG_CONTROL, Node->ControlRegister.byte);
        }
    }
    return res;
}

bool sa51034_gain_set(uint8_t num, Gain_t gain_db) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            Node->ControlRegister.gain = Sa51GainToCode(gain_db);
            res = sa51034_reg_write_ll(Node, SA51034_REG_CONTROL, Node->ControlRegister.byte);
        }
    }
    return res;
}

bool sa51034_power_limit_set(uint8_t num, double power_limit) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            Node->ControlRegister.power_limit = Sa51PowerLimitToCode(power_limit);
            res = sa51034_reg_write_ll(Node, SA51034_REG_CONTROL, Node->ControlRegister.byte);
        }
    }
    return res;
}

bool sa51034_power_limit_get(uint8_t num, double* const power_limit) {
    bool res = false;
    Sa51034Handle_t* Node = Sa51034GetNode(num);
    if(Node) {
        res = sa51034_reg_read_ll(Node, SA51034_REG_CONTROL, &Node->ControlRegister.byte);
        if(res) {
            *power_limit = Sa51PowerLimitCodeToVolts(Node->ControlRegister.power_limit);
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(SA51034, SA51034, sa51034)
COMPONENT_PROC_PATTERT(SA51034, SA51034, sa51034)
