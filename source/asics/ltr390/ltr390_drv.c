#include "ltr390_drv.h"

/*
 * LTR-390UV-01 Ultraviolet Sensor Review
 * https://habr.com/ru/articles/789492/
 */

#include "byte_utils.h"
#include "code_generator.h"
#include "gpio_mcal.h"
#include "i2c_mcal.h"
#include "log.h"
#include "ltr390_config.h"
#include "ltr390_dep.h"
#include "utils_math.h"

Ltr390GainVal_t GainCode2Val(uint8_t code) {
    Ltr390GainVal_t gain_val = LTR390_GAIN_VAL_UDEF;
    switch(code) {
    case LTR390_GAIN_CODE_1:
        gain_val = LTR390_GAIN_VAL_1;
        break;
    case LTR390_GAIN_CODE_3:
        gain_val = LTR390_GAIN_VAL_3;
        break;
    case LTR390_GAIN_CODE_6:
        gain_val = LTR390_GAIN_VAL_6;
        break;
    case LTR390_GAIN_CODE_9:
        gain_val = LTR390_GAIN_VAL_9;
        break;
    case LTR390_GAIN_CODE_18:
        gain_val = LTR390_GAIN_VAL_18;
        break;
    }
    return gain_val;
}

#define REG_ENTRY(REG_NAME, SIZE, ACCESS)                                                                              \
    { .valid = true, .address = LTR390_REG_ADDR_##REG_NAME, .name = #REG_NAME, .size = SIZE, .access = ACCESS, }

static const Ltr390RegisterInfo_t Ltr390RegisterInfo[] = {
    REG_ENTRY(MAIN_CTRL, 1, REG_ACCESS_READ_WRITE), REG_ENTRY(MEAS_RATE, 1, REG_ACCESS_READ_WRITE),
    REG_ENTRY(GAIN, 1, REG_ACCESS_READ_WRITE),      REG_ENTRY(PART_ID, 1, REG_ACCESS_READ),
    REG_ENTRY(MAIN_STATUS, 1, REG_ACCESS_READ),     REG_ENTRY(ALS_DATA, 3, REG_ACCESS_READ),
    REG_ENTRY(UVS_DATA, 3, REG_ACCESS_READ),        REG_ENTRY(INT_CFG, 1, REG_ACCESS_READ_WRITE),
    REG_ENTRY(INT_PST, 1, REG_ACCESS_READ_WRITE),   REG_ENTRY(THRES_UP, 3, REG_ACCESS_READ_WRITE),
    REG_ENTRY(THRES_LOW, 3, REG_ACCESS_READ_WRITE),
};

COMPONENT_GET_NODE(Ltr390, ltr390)

COMPONENT_GET_CONFIG(Ltr390, ltr390)

uint32_t lrt390_info_get_cnt(void) { return ARRAY_SIZE(Ltr390RegisterInfo); }

const Ltr390RegisterInfo_t* Ltr390RegisterInfoGet(uint8_t address) {
    Ltr390RegisterInfo_t* InfoNode = NULL;
    uint32_t i = 0;
    for(i = 0; i < lrt390_info_get_cnt(); i++) {
        if(address == Ltr390RegisterInfo[i].address) {
            if(Ltr390RegisterInfo[i].valid) {
                InfoNode = &Ltr390RegisterInfo[i];
                break;
            }
            break;
        }
    }
    return InfoNode;
}

bool ltr390_register_read(uint8_t num, uint8_t addr, uint8_t* const value) {
    bool res = false;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        LOG_PARN(LTR390, "RegRead %u,Addr:0x%02x", num, addr);
        if(value) {
            res = i2c_mcal_read_byte(Node->i2c_num, LTR390_I2C_ADDR, addr, value);
            if(res) {
                LOG_PARN(LTR390, "RegReadOk Addr:0x%02x", addr, *value);
            } else {
                LOG_ERROR(LTR390, "LTR390%u,RegReadErr,Addr:0x%02x", num, addr);
            }
        }
    }
    return res;
}

bool ltr390_register_write(uint8_t num, uint8_t addr, uint8_t val_set) {
    bool res = false;
    LOG_PARN(LTR390, "RegWrite %u,Addr:0x%02x,Val:0x%02x", num, addr, val_set);
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        res = i2c_api_reg_write(Node->i2c_num, LTR390_I2C_ADDR, addr, val_set);
        if(res) {
            LOG_PARN(LTR390, "RegWrireOk Addr:0x%02x", addr, val_set);
        } else {
            LOG_ERROR(LTR390, "RegWrireErr %u,Addr:0x%02x", num, addr);
        }
    }
    return res;
}

const Ltr390ResolutionInfo_t Ltr390ResolutionInfo[] = {
    {
        .code = LTR390_RESOLUTION_CODE_20_BIT,
        .val = LTR390_RESOLUTION_VAL_20_BIT,
        .integration_time = 4.0,
    },
    {
        .code = LTR390_RESOLUTION_CODE_19_BIT,
        .val = LTR390_RESOLUTION_VAL_19_BIT,
        .integration_time = 2.0,
    },
    {
        .code = LTR390_RESOLUTION_CODE_18_BIT,
        .val = LTR390_RESOLUTION_VAL_18_BIT,
        .integration_time = 1.0,
    },
    {
        .code = LTR390_RESOLUTION_CODE_17_BIT,
        .val = LTR390_RESOLUTION_VAL_17_BIT,
        .integration_time = 0.5,
    },
    {
        .code = LTR390_RESOLUTION_CODE_16_BIT,
        .val = LTR390_RESOLUTION_VAL_16_BIT,
        .integration_time = 0.25,
    },
    {
        .code = LTR390_RESOLUTION_CODE_13_BIT,
        .val = LTR390_RESOLUTION_VAL_13_BIT,
        .integration_time = 0.03125,
    },
    {
        .code = LTR390_RESOLUTION_CODE_RES1_BIT,
        .val = 0,
        .integration_time = 0.0,
    },
    {
        .code = LTR390_RESOLUTION_CODE_RES2_BIT,
        .val = 0,
        .integration_time = 0.0,
    },
};

double ResolutionToIntergationTime(ResolutionVal_t resolution) {
    double intergation_time = 0.0;
    switch((uint8_t)resolution) {
    case LTR390_RESOLUTION_VAL_20_BIT:
        intergation_time = 4.0;
        break;
    case LTR390_RESOLUTION_VAL_19_BIT:
        intergation_time = 2.0;
        break;
    case LTR390_RESOLUTION_VAL_18_BIT:
        intergation_time = 1.0;
        break;
    case LTR390_RESOLUTION_VAL_17_BIT:
        intergation_time = 0.5;
        break;
    case LTR390_RESOLUTION_VAL_16_BIT:
        intergation_time = 0.25;
        break;
    case LTR390_RESOLUTION_VAL_13_BIT:
        intergation_time = 0.0;
        break;
    }
    return intergation_time;
}

bool ltr390_integration_time_get(uint8_t num, double* const intergation_time) {
    bool res = false;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        *intergation_time = ResolutionToIntergationTime(Node->resolution);
    }
    return res;
}

bool ltr390_gain_get(uint8_t num, Ltr390GainVal_t* const gain_range) {
    bool res = false;
    LOG_PARN(LTR390, "GainRead %u", num);
    Ltr390RegAlsUvsGain_t AlsUvsGain;
    AlsUvsGain.byte = 0;
    res = ltr390_register_read(num, LTR390_REG_ADDR_GAIN, &AlsUvsGain.byte);
    if(res) {
        *gain_range = GainCode2Val(AlsUvsGain.gain);
    }
    return res;
}

bool ltr390_register_write_lazy(uint8_t num, uint8_t addr, uint8_t val_set) {
    bool res = false;
    LOG_DEBUG(LTR390, "RegWriteLazy %u,Addr:0x%02x,Val:0x%02x", num, addr, val_set);
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        uint8_t read_value = 0;
        res = ltr390_register_read(num, addr, &read_value);
        if(res) {
            if(val_set != read_value) {
                res = i2c_api_reg_write(Node->i2c_num, LTR390_I2C_ADDR, addr, val_set);
                if(res) {
                    LOG_DEBUG(LTR390, "RegWrireOk Addr:0x%02x", addr, val_set);
                } else {
                    LOG_ERROR(LTR390, "RegWrireErr %u,Addr:0x%02x", num, addr);
                }
            } else {
                LOG_DEBUG(LTR390, "RegWrireNoNeed Addr:0x%02x", addr, val_set);
            }
        }
    }
    return res;
}

bool ltr390_is_connected_ll(Ltr390Handle_t* const Node) {
    bool res = false;
    uint8_t value = 0;
    res = ltr390_register_read(Node->num, LTR390_REG_ADDR_PART_ID, &value);
    if(res) {
        res = false;
        if(LTR390_REV_CODE == value) {
            res = true;
        }
    }
    return res;
}

bool ltr390_is_connected(uint8_t num) {
    bool res = false;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        res = ltr390_is_connected_ll(Node);
    }
    return res;
}

bool ltr390_init_one(uint8_t num) {
    bool res = false;
    const Ltr390Config_t* Config = Ltr390GetConfig(num);
    if(Config) {
        LOG_WARNING(LTR390, "%s", Ltr390ConfigToStr(Config));
        Ltr390Handle_t* Node = Ltr390GetNode(num);
        if(Node) {
            uint32_t err_cnt = 0;
            LOG_WARNING(LTR390, "Init LTR390_%u", num);
            Node->i2c_num = Config->i2c_num;
            Node->name = Config->name;
            Node->irq = Config->irq;
            Node->num = Config->num;
            Node->valid = true;
            log_level_get_set(I2C, LOG_LEVEL_DEBUG);
            log_level_get_set(LTR390, LOG_LEVEL_DEBUG);
            res = ltr390_is_connected_ll(Node);
            if(res) {
                LOG_INFO(LTR390, "%u,Connected!", num);
                uint32_t reg_cnt = 0;
                uint32_t i = 0;
                reg_cnt = ltr390_reg_get_cnt();
                for(i = 0; i < reg_cnt; i++) {
                    res = ltr390_register_write(num, Ltr390Register[i].address, Ltr390Register[i].value.byte);
                    if(res) {

                    } else {
                        err_cnt++;
                    }
                }

                if(err_cnt) {
                    res = false;
                }
                res = ltr390_start_measurement(num, LTR390_SRC_ALS);
            } else {
                LOG_ERROR(LTR390, "%u,Disconnected", num);
            }
            log_level_get_set(I2C, LOG_LEVEL_INFO);
            log_level_get_set(LTR390, LOG_LEVEL_INFO);
        }
    }
    return res;
}

double Ltr390Code2Lx(uint32_t qword) {
    double lx = 0;
    return lx;
}

Ltr390LsInterruptSelect_t Ltr390SourseToIntSel(DataSource_t source) {
    Ltr390LsInterruptSelect_t LsInterruptSelect = LTR390_INT_SEL_RES1;
    switch(source) {
    case LTR390_SRC_ALS:
        LsInterruptSelect = LTR390_INT_SEL_ALS_CHANNEL;
        break;
    case LTR390_SRC_UVS:
        LsInterruptSelect = LTR390_INT_SEL_UVS_CHANNEL;
        break;
    default:
        break;
    }
    return LsInterruptSelect;
}

bool ltr390_start_measurement_ll(Ltr390Handle_t* Node, DataSource_t source) {
    bool res = false;
    if(Node) {
        LOG_PARN(LTR390, "StartMeasure:%u=%s", source, SourceToStr(source));
        /*see 6.8*/
        Ltr390RegIntCfg_t IntCfg;
        IntCfg.byte = 0;
        IntCfg.ls_int_en = LTR390_INT_ENABLE;
        IntCfg.ls_int_sel = Ltr390SourseToIntSel(source);
        res = ltr390_register_write(Node->num, LTR390_REG_ADDR_INT_CFG, IntCfg.byte);

        Ltr390RegMainCtrl_t MainCtrl;
        MainCtrl.byte = 0;
        MainCtrl.enable = LTR390_LS_ACTIVE;
        MainCtrl.uvs_mode = source;
        MainCtrl.soft_reset = LTR390_NO_RESET;
        res = ltr390_register_write(Node->num, LTR390_REG_ADDR_MAIN_CTRL, MainCtrl.byte);

        Node->cur_source = source;
    }
    return res;
}

bool ltr390_start_measurement(uint8_t num, DataSource_t source) {
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    bool res = false;
    if(Node) {
        res = ltr390_start_measurement_ll(Node, source);
    }
    return res;
}

bool ltr390_read_code_uvs_ll(Ltr390Handle_t* Node, uint32_t* const qword) {
    bool res = false;
    if(Node) {
        res = ltr390_start_measurement_ll(Node, LTR390_SRC_UVS);
#if 0
        Node->uvs_data.u32 = 0;
        uint8_t addr = 0;
        addr = LTR390_REG_ADDR_UVS_DATA;
        res = i2c_mcal_read_mem(Node->i2c_num, LTR390_I2C_ADDR, &addr, 1, Node->uvs_data.u8, 3);
        if(res) {
            LOG_DEBUG(UVS, "%u UVScode:%u", Node->num, Node->uvs_data.u32);
            *qword = Node->uvs_data.u32;
        } else {
            LOG_ERROR(UVS, "UVSReadMemErr");
        }
#endif
    }
    return res;
}

bool ltr390_read_code_uvs(uint8_t num, uint32_t* const qword) {
    bool res = false;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        res = ltr390_read_code_uvs_ll(Node, qword);
    }
    return res;
}

bool ltr390_read_code_als_ll(Ltr390Handle_t* Node) {
    bool res = false;
    res = ltr390_start_measurement_ll(Node, LTR390_SRC_ALS);
#if 0
    uint8_t addr = 0;
    addr = LTR390_REG_ADDR_ALS_DATA;
    Node->als_data.u32 = 0;
    res = i2c_mcal_read_mem(Node->i2c_num, LTR390_I2C_ADDR, &addr, 1, Node->als_data.u8, 3);
    if(res) {
        LOG_DEBUG(ALS, "%u ALScode:%u", Node->num, Node->als_data.u32);
        *qword = Node->als_data.u32;
    } else {
        LOG_ERROR(ALS, "ALSReadMemErr");
    }
#endif
    return res;
}

bool ltr390_read_code_als(uint8_t num, uint32_t* const qword) {
    bool res = false;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        res = ltr390_read_code_als_ll(Node);
    }
    return res;
}

bool ltr390_als_code_to_lx(Ltr390Handle_t* Node) {
    bool res = false;
    /*see 7.1 page 24*/
    if(Node) {
        if(Node->gain) {
            if(0.0 < Node->integratin_time_factor) {

                Node->als_lx =
                    0.6 * ((double)Node->als_data.u32) / (((double)Node->gain) * Node->integratin_time_factor);
                res = true;
            }
        }
    }
    return res;
}

bool ltr390_uvs_code_to_uvi(Ltr390Handle_t* Node) {
    bool res = false;
    /*see 7.1 page 24*/
    if(Node) {
        if(Node->gain) {
            /*Only for 20 bit */
            Node->uvi = ((double)Node->uvs_data.u32) / (((double)UV_SENSITIVITY));
            res = true;
        }
    }
    return res;
}

ResolutionVal_t ResolutionCodeToResolution(uint8_t code) {
    ResolutionVal_t resolution_val = LTR390_RESOLUTION_VAL_UNDEF;
    switch(code) {
    case LTR390_RESOLUTION_CODE_20_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_20_BIT;
        break;
    case LTR390_RESOLUTION_CODE_19_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_19_BIT;
        break;
    case LTR390_RESOLUTION_CODE_18_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_18_BIT;
        break;
    case LTR390_RESOLUTION_CODE_17_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_17_BIT;
        break;
    case LTR390_RESOLUTION_CODE_16_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_16_BIT;
        break;
    case LTR390_RESOLUTION_CODE_13_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_13_BIT;
        break;
    case LTR390_RESOLUTION_CODE_RES1_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_UNDEF;
        break;
    case LTR390_RESOLUTION_CODE_RES2_BIT:
        resolution_val = LTR390_RESOLUTION_VAL_UNDEF;
        break;
    }
    return resolution_val;
}

bool ltr390_resolution_get(uint8_t num, ResolutionVal_t* const resolution) {
    bool res = false;
    Ltr390RegMeasRate_t MeasRate;
    MeasRate.byte = 0;
    res = ltr390_register_read(num, LTR390_REG_ADDR_MEAS_RATE, &MeasRate.byte);
    if(res) {
        *resolution = ResolutionCodeToResolution(MeasRate.resolution);
    }
    return res;
}

static DataSource_t Ltr390ToggleSrc(DataSource_t cur_source) {
    DataSource_t out_src = LTR390_SRC_UNDEF;
    LOG_PARN(UVS, "ToggleSrc:%u", cur_source);
    switch((uint8_t)cur_source) {
    case LTR390_SRC_ALS:
        out_src = LTR390_SRC_UVS;
        break;
    case LTR390_SRC_UVS:
        out_src = LTR390_SRC_ALS;
        break;
    }
    return out_src;
}

bool ltr390_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(LTR390, "Proc %u", num);
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        res = ltr390_gain_get(num, &Node->gain);
        res = ltr390_resolution_get(num, &Node->resolution);
        res = ltr390_integration_time_get(num, &Node->integratin_time_factor);

        Ltr390RegMainStatus_t MainStatus;
        MainStatus.byte = 0;
        res = ltr390_register_read(num, LTR390_REG_ADDR_MAIN_STATUS, &MainStatus.byte);
        if(res) {
            if(MainStatus.interrupt_status) {
                LOG_WARNING(LTR390, "LTR_%u Interrupt!", num);
            }
            if(MainStatus.power_on_status) {
                LOG_WARNING(LTR390, "LTR_%u PowerOn!", num);
            }

            if(MainStatus.data_status) {
                Node->new_data_cnt++;
                LOG_DEBUG(LTR390, "LTR_%u NewData!,Src:%s,AL:%7.3f lx,UV:%7.3f uvi", num, SourceToStr(Node->cur_source),
                          Node->als_lx, Node->uvi);

                uint8_t addr = 0;
                switch((uint8_t)Node->cur_source) {
                case LTR390_SRC_ALS: {
                    addr = LTR390_REG_ADDR_ALS_DATA;
                    Node->als_data.u32 = 0;
                    res = i2c_mcal_read_mem(Node->i2c_num, LTR390_I2C_ADDR, &addr, 1, Node->als_data.u8, 3);
                    if(res) {
                        res = ltr390_als_code_to_lx(Node);
                        LOG_DEBUG(ALS, "%u code:%u,Lx:%f lx", Node->num, Node->als_data.u32, Node->als_lx);
                    } else {
                        LOG_ERROR(ALS, "ReadMemErr");
                    }
                } break;
                case LTR390_SRC_UVS: {
                    addr = LTR390_REG_ADDR_UVS_DATA;
                    Node->uvs_data.u32 = 0;
                    res = i2c_mcal_read_mem(Node->i2c_num, LTR390_I2C_ADDR, &addr, 1, Node->uvs_data.u8, 3);
                    if(res) {
                        res = ltr390_uvs_code_to_uvi(Node);
                        LOG_DEBUG(UVS, "%u code:%u", Node->num, Node->uvs_data.u32, Node->uvi);
                    } else {
                        LOG_ERROR(UVS, "ReadMemErr");
                    }
                } break;
                }
                Node->new_data = true;
                res = ltr390_start_measurement_ll(Node, Ltr390ToggleSrc(Node->cur_source));
            }
        }
        GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
        res = gpio_get_state(Node->irq, &logic_level);
        if(res) {
            if(GPIO_LVL_LOW == logic_level) {
                LOG_WARNING(LTR390, "LTR%u Interrupt!", num);
            }
        }
#if 0
        uint32_t qword = 0;
        qword = 0;
        res = ltr390_read_code_als_ll(Node);
        if(res) {
            LOG_INFO(ALS, "ReadOk,Code:%u", qword);
        } else {
            LOG_ERROR(ALS, "ReadErr %u", num);
        }

        qword = 0;
        res = ltr390_read_code_uvs_ll(Node, &qword);
        if(res) {
            LOG_INFO(UVS, "ReadOk,Code:%u", qword);
        } else {
            LOG_ERROR(UVS, "ReadErr %u", num);
        }
#endif
    }
    return res;
}

double ltr390_read_lx_short(uint8_t num) {
    double val = 0.0;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        val = Node->als_lx;
    }
    return val;
}

double ltr390_read_uv_short(uint8_t num) {
    double val = 0.0;
    Ltr390Handle_t* Node = Ltr390GetNode(num);
    if(Node) {
        val = Node->uvi;
    }
    return val;
}

bool ltr390_is_valid_reg_addr(uint8_t reg_addr) {
    bool res = false;
    uint32_t i = 0;
    for(i = 0; i < lrt390_info_get_cnt(); i++) {
        if(Ltr390RegisterInfo[i].address <= reg_addr) {
            if(reg_addr < (Ltr390RegisterInfo[i].address + Ltr390RegisterInfo[i].size)) {
                res = true;
                break;
            }
        }
    }
    return res;
}

static bool ltr390_init_custom(void) {
    bool res = true;
    return res;
}

bool ltr390_reset(uint8_t num) {
    bool res = false;
    LOG_WARNING(LTR390, "Reset %u", num);
    Ltr390RegMainCtrl_t MainCtrl = {0};
    MainCtrl.byte = 0;
    res = ltr390_register_read(num, LTR390_REG_ADDR_MAIN_CTRL, &MainCtrl.byte);
    if(res) {
        MainCtrl.soft_reset = 1;
        res = ltr390_register_write(num, LTR390_REG_ADDR_MAIN_CTRL, MainCtrl.byte);
    }
    return res;
}

COMPONENT_INIT_PATTERT(LTR390, LTR390, ltr390)

COMPONENT_PROC_PATTERT(LTR390, LTR390, ltr390)
