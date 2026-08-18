#include "fda801_drv.h"

#ifdef HAS_COMMON
#include "common_const.h"
#include "common_diag.h"
#endif

#ifdef HAS_AUDIO
#include "audio_types.h"
#endif

#include "bit_utils.h"
#ifdef HAS_CLOCK
#include "clocks.h"
#endif

#include "fda801_config.h"
#ifdef HAS_FDA801_DIAG
#include "fda801_diag.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_I2S
#include "i2s_config.h"
#include "i2s_drv.h"
#endif /*HAS_I2S*/

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif /*HAS_GPIO*/

#ifdef HAS_I2C
#include "i2c_bsp.h"
#include "i2c_config.h"
#include "i2c_mcal.h"
#endif /*HAS_I2C*/

const Fda801Reg_t Fda801RegMap[FDA801_REG_CNT] = {{
                                                      .reg_addr = REG_INTERFACE,
                                                      .name = "Interface",
                                                  },
                                                  {
                                                      .reg_addr = 1,
                                                      .name = "CR1",
                                                  },
                                                  {
                                                      .reg_addr = 2,
                                                      .name = "Diag",
                                                  },
                                                  {
                                                      .reg_addr = 3,
                                                      .name = "CR2",
                                                  },
                                                  {
                                                      .reg_addr = 4,
                                                      .name = "DiagSel",
                                                  },
                                                  {
                                                      .reg_addr = 5,
                                                      .name = "Chn1Cntr",
                                                  },
                                                  {
                                                      .reg_addr = 6,
                                                      .name = "Chn2Cntr",
                                                  },
                                                  {
                                                      .reg_addr = 7,
                                                      .name = "Chn3Cntr",
                                                  },
                                                  {
                                                      .reg_addr = 8,
                                                      .name = "Chn4Cntr",
                                                  },
                                                  {
                                                      .reg_addr = 9,
                                                      .name = "DiagPhaseDelayCntrCh1",
                                                  },
                                                  {
                                                      .reg_addr = 10,
                                                      .name = "DiagPhaseDelayCntrCh2",
                                                  },
                                                  {
                                                      .reg_addr = 11,
                                                      .name = "DiagPhaseDelayCntrCh3",
                                                  },
                                                  {
                                                      .reg_addr = 12,
                                                      .name = "DiagPhaseDelayCntrCh4",
                                                  },
                                                  {
                                                      .reg_addr = 13,
                                                      .name = "Digital",
                                                  },
                                                  {
                                                      .reg_addr = 14,
                                                      .name = "LCFilterSetup",
                                                  },
                                                  {
                                                      .reg_addr = 32,
                                                      .name = "Sensor",
                                                  },
                                                  {
                                                      .reg_addr = 33,
                                                      .name = "ThermalWarning",
                                                  },
                                                  {
                                                      .reg_addr = 34,
                                                      .name = "Chn1DcOut",
                                                  },
                                                  {
                                                      .reg_addr = 35,
                                                      .name = "Chn2DcOut",
                                                  },
                                                  {
                                                      .reg_addr = 36,
                                                      .name = "Chn3DcOut",
                                                  },
                                                  {
                                                      .reg_addr = 37,
                                                      .name = "Chn4DcOut",
                                                  },
                                                  {
                                                      .reg_addr = 38,
                                                      .name = "Ch1Ch2AcDiagRes",
                                                  },
                                                  {
                                                      .reg_addr = 39,
                                                      .name = "Ch3Ch4AcDiagRes",
                                                  }};

const Fda801I2cAddr_t Fda801I2cAddr[4] = {
    {.addr = FDA801_ADDRESS1, .code.en1 = 0, .code.en2 = 1, .code.en3 = 0},
    {.addr = FDA801_ADDRESS2, .code.en1 = 1, .code.en2 = 1, .code.en3 = 0},
    {.addr = FDA801_ADDRESS3, .code.en1 = 0, .code.en2 = 0, .code.en3 = 1},
    {.addr = FDA801_ADDRESS4, .code.en1 = 0, .code.en2 = 1, .code.en3 = 1},
};

static Fda801RegData_t Fda801RegData[FDA801_REG_CNT] = {{
                                                            .addr = REG_INTERFACE,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CR1,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAG,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CR2,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAGSEL,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN1CNTR,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN2CNTR,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN3CNTR,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN4CNTR,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAGPHASEDELAYCNTRCH1,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAGPHASEDELAYCNTRCH2,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAGPHASEDELAYCNTRCH3,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIAGPHASEDELAYCNTRCH4,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_DIGITAL,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_LCFILTERSETUP,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_SENSOR,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_THERMALWARNING,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN1DCOUT,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN2DCOUT,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN3DCOUT,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CHN4DCOUT,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CH1CH2ACDIAGRES,
                                                            .value = 0,
                                                        },
                                                        {
                                                            .addr = REG_CH3CH4ACDIAGRES,
                                                            .value = 0,
                                                        }};

static uint8_t fda_get_reg_val_cache(uint8_t addr) {
    uint8_t reg_val = 0, i = 0;
    for(i = 0; i < ARRAY_SIZE(Fda801RegData); i++) {
        if(Fda801RegData[i].addr == addr) {
            reg_val = Fda801RegData[i].value;
            break;
        }
    }
    return reg_val;
}

const Fda801Config_t* Fda801GetConfNode(uint8_t id_num) {
    const Fda801Config_t* ConfNode = NULL;
    uint32_t fda801_cnt = fda801_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < fda801_cnt; i++) {
        if(Fda801Config[i].num == id_num) {
            ConfNode = &Fda801Config[i];
            break;
        }
    }
    return ConfNode;
}

Fda801Handle_t* Fda801GetNode(uint8_t id_num) {
    Fda801Handle_t* ConfNode = NULL;
    uint32_t fda801_cnt = fda801_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < fda801_cnt; i++) {
        if(Fda801Config[i].num == id_num) {
            ConfNode = &Fda801Instance[i];
            break;
        }
    }
    return ConfNode;
}

static const Channal2Regs_t Channal2RegsLut[FDA801_CHANNEL_COUNT] = {
    {
        .channal = 1,
        .RegAddr.dc_output = REG_CHN1DCOUT,
        .RegAddr.ctrl = REG_CHN1CNTR,
        .RegAddr.ac_diag = REG_CH1CH2ACDIAGRES,
    },
    {
        .channal = 2,
        .RegAddr.dc_output = REG_CHN2DCOUT,
        .RegAddr.ctrl = REG_CHN2CNTR,
        .RegAddr.ac_diag = REG_CH1CH2ACDIAGRES,
    },
    {
        .channal = 3,
        .RegAddr.dc_output = REG_CHN3DCOUT,
        .RegAddr.ctrl = REG_CHN3CNTR,
        .RegAddr.ac_diag = REG_CH3CH4ACDIAGRES,
    },
    {
        .channal = 4,
        .RegAddr.dc_output = REG_CHN4DCOUT,
        .RegAddr.ctrl = REG_CHN4CNTR,
        .RegAddr.ac_diag = REG_CH3CH4ACDIAGRES,
    },

};

static const Channal2Regs_t* fda801_get_chan_regs(Fda801ChannelNum_t chan) {
    const Channal2Regs_t* Channal2Regs = NULL;
    bool res = fda801_is_valid_channel(chan);
    if(res) {
        Channal2Regs = &Channal2RegsLut[chan - 1];
    }
    return Channal2Regs;
}

static bool fda801_rarse_chan_ac_diag(Fda801ChannelNum_t chan, uint8_t reg_val) {
    bool res = false;
    Fda801Channel_t* Channel = fda801_get_channel_node(chan);
    if(Channel) {
        res = true;
        Fda801RegChAcDiag_t Reg;
        Reg.reg_val = reg_val;

        switch(chan) {
        case FDA_CHANNEL_1:
            Channel->AcDiag.operation = Reg.ch1_operation;
            Channel->AcDiag.tweeter = Reg.ch1_tweeter;
            Channel->AcDiag.warning = Reg.ch1_error_warning;
            Channel->AcDiag.valid = Reg.ch1_ac_diag_data;
            break;
        case FDA_CHANNEL_2:
            Channel->AcDiag.operation = Reg.ch2_operation;
            Channel->AcDiag.tweeter = Reg.ch2_tweeter;
            Channel->AcDiag.warning = Reg.ch2_error_warning;
            Channel->AcDiag.valid = Reg.ch2_ac_diag_data;

            break;
        case FDA_CHANNEL_3:
            Channel->AcDiag.operation = Reg.ch3_operation;
            Channel->AcDiag.tweeter = Reg.ch3_tweeter;
            Channel->AcDiag.warning = Reg.ch3_error_warning;
            Channel->AcDiag.valid = Reg.ch3_ac_diag_data;
            break;
        case FDA_CHANNEL_4:
            Channel->AcDiag.operation = Reg.ch4_operation;
            Channel->AcDiag.tweeter = Reg.ch4_tweeter;
            Channel->AcDiag.warning = Reg.ch4_error_warning;
            Channel->AcDiag.valid = Reg.ch4_ac_diag_data;

            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

static bool fda801_rarse_chan_control(Fda801ChannelNum_t chan, uint8_t reg_val) {
    bool res = false;
    Fda801Channel_t* Channel = fda801_get_channel_node(chan);
    if(Channel) {
        Fda801RegChannelCtrl_t Reg;
        Reg.reg_val = reg_val;
        Channel->Reg.state = Reg.chx_status;
        Channel->Reg.ac_diag = Reg.chx_ac_diag;
        Channel->Reg.dc_diag = Reg.chx_dc_diag;
        Channel->Reg.diag = Reg.chx_diag;
        Channel->Reg.pwm_on = Reg.chx_pwm;
        Channel->Reg.gain_sel = Reg.chx_gain_sel;
        Channel->Reg.ac_ext_test_flag = Reg.chx_ac_ext_test;
    }
    return res;
}

static bool fda801_rarse_dc_output(Fda801ChannelNum_t chan, uint8_t reg_val) {
    bool res = false;
    Fda801Channel_t* Channel = fda801_get_channel_node(chan);
    if(Channel) {
        Fda801RegChDcOut_t Reg;
        Reg.reg_val = reg_val;

        if(Reg.state) {
            Channel->DcOutput.state = 1;
#ifdef HAS_LOG
            LOG_DEBUG(FDA801, "Ch%u Play", chan);
#endif
        }

        if(Reg.dc_op) {
            Channel->DcOutput.operation = 1;
#ifdef HAS_LOG
            LOG_INFO(FDA801, "Ch%u DiagPulseEnd", chan);
#endif
        }
        if(Reg.dc_diag_dat_valid) {
            Channel->DcDiag = DC_DIAG_OK;
            Channel->DcOutput.dc_diag_dat_valid = 1;
#ifdef HAS_LOG
            LOG_INFO(FDA801, "Ch%u DiagValid", chan);
#endif
        }
        if(Reg.load_open) {
            Channel->DcDiag = DC_DIAG_OPEN_LOAD;
            Channel->DcOutput.load_open = 1;
#ifdef HAS_LOG
            LOG_WARNING(FDA801, "Ch%u OpenLoad", chan);
#endif
        }
        if(Reg.load_short) {
            Channel->DcOutput.load_short = 1;
            Channel->DcDiag = DC_DIAG_SHORT_LOAD;
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "Ch%u ShortLoad", chan);
#endif
        }
        if(Reg.short_gnd) {
            Channel->DcDiag = DC_DIAG_SHORT_GND;
            Channel->DcOutput.short_gnd = 1;
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "Ch%u ShortGnd", chan);
#endif
        }
        if(Reg.short_vcc) {
            Channel->DcDiag = DC_DIAG_SHORT_VCC;
            Channel->DcOutput.short_vcc = 1;
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "Ch%u ShortVcc", chan);
#endif
        }
        if(Reg.over_current) {
            Channel->DcDiag = DC_DIAG_OVERCURRTNT;
            Channel->DcOutput.over_current = 1;
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "Ch%u OverCurrent", chan);
#endif
        }
    }

    return res;
}

bool fda801_proc(void) {
    bool res = false;

    Fda801Handle_t* Fda801Node = Fda801GetNode(FDA801_MAIN);
    if(Fda801Node->init) {
        if(Fda801Node) {
            Fda801Node->spin_cnt++;
            uint8_t reg_val = 0;
            uint8_t ch = 0;
            for(ch = 1; ch <= FDA801_CHANNEL_COUNT; ch++) {
                reg_val = fda_get_reg_val_cache(Channal2RegsLut[ch - 1].RegAddr.dc_output);
                res = fda801_rarse_dc_output(ch, reg_val);

                reg_val = fda_get_reg_val_cache(Channal2RegsLut[ch - 1].RegAddr.ctrl);
                res = fda801_rarse_chan_control(ch, reg_val);

                reg_val = fda_get_reg_val_cache(Channal2RegsLut[ch - 1].RegAddr.ac_diag);
                res = fda801_rarse_chan_ac_diag(ch, reg_val);
            }
        }
        uint32_t i = 0, cnt = 0;
        uint32_t total = ARRAY_SIZE(Fda801RegData);
        for(i = 0; i < total; i++) {
            res = fda801_read_reg(Fda801RegData[i].addr, &Fda801RegData[i].value);
            if(false == res) {
#ifdef HAS_FDA801_DIAG
                LOG_ERROR(FDA801, "RegReadErr Addr:0x%02x [%s]", Fda801RegData[i].addr,
                          fda801_get_reg_name(Fda801RegData[i].addr));
#endif
            } else {
                cnt++;
            }
        }
        if(cnt == total) {
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}

uint8_t fda801_get_chip_addr(uint8_t id_num) {
    uint8_t i2c_addr = 0;
    const Fda801Config_t* Fda801Node = Fda801GetConfNode(id_num);
    if(Fda801Node) {
        uint8_t logic_level = 0;
        bool res = true;
        Fda801I2cAddr_t I2cAddrNode;
        res = gpio_get_state(Fda801Node->gpio.en1.byte, &logic_level) && res;
#ifdef HAS_LOG
        LOG_DEBUG(FDA801, "EN1 %u", logic_level);
#endif
        I2cAddrNode.code.en1 = logic_level;

        res = gpio_get_state(Fda801Node->gpio.en2.byte, &logic_level) && res;
#ifdef HAS_LOG
        LOG_DEBUG(FDA801, "EN2 %u", logic_level);
#endif
        I2cAddrNode.code.en2 = logic_level;

        res = gpio_get_state(Fda801Node->gpio.en3.byte, &logic_level) && res;
#ifdef HAS_LOG
        LOG_DEBUG(FDA801, "EN3 %u", logic_level);
#endif
        I2cAddrNode.code.en3 = logic_level;
        I2cAddrNode.code.byte = MASK_3BIT & I2cAddrNode.code.byte;
        uint8_t i = 0;
        res = false;
#ifdef HAS_LOG
        LOG_DEBUG(FDA801, "EnCode %u", I2cAddrNode.code.byte);
#endif
        for(i = 0; i < ARRAY_SIZE(Fda801I2cAddr); i++) {
            if(Fda801I2cAddr[i].code.byte == I2cAddrNode.code.byte) {
                i2c_addr = Fda801I2cAddr[i].addr;
#ifdef HAS_LOG
                LOG_DEBUG(FDA801, "SpotAddr 0x%x", Fda801I2cAddr[i].addr);
#endif
                res = true;
                break;
            }
        }
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "UndefEnCode 0x%x", I2cAddrNode.code.byte);
#endif
        }
    }
    return i2c_addr;
}

bool fda801_set_chip_addr(uint8_t addr) {
    bool res = false;
    uint8_t i = 0;
    LOG_INFO(FDA801, "SetChipAddr 0x%x", addr);
    for(i = 0; i < ARRAY_SIZE(Fda801I2cAddr); i++) {
        if(addr == Fda801I2cAddr[i].addr) {
            const Fda801Config_t* ConfNode = Fda801GetConfNode(FDA801_MAIN);
            if(ConfNode) {
                res = true;
                LOG_INFO(FDA801, "PinCode 0x%02x", Fda801I2cAddr[i].code);
                res = gpio_set_state_verify(ConfNode->gpio.en1.byte, Fda801I2cAddr[i].code.en1) && res;
                res = gpio_set_state_verify(ConfNode->gpio.en2.byte, Fda801I2cAddr[i].code.en2) && res;
                res = gpio_set_state_verify(ConfNode->gpio.en3.byte, Fda801I2cAddr[i].code.en3) && res;
            }
            break;
        }
    }
    return res;
}

uint32_t fda801_reg_cnt(void) { return ARRAY_SIZE(Fda801RegMap); }

bool fda801_read_reg(uint8_t reg_addr, uint8_t* reg_val) {
    bool res = false;
    const Fda801Config_t* FdaConfNode = Fda801GetConfNode(FDA801_MAIN);
    if(FdaConfNode) {
#ifdef HAS_I2C
        res = i2c_mcal_read_byte(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr, reg_addr, reg_val);
        if(false == res) {
            LOG_ERROR(I2C, "Num:%u ReadReg Reg:0x%02X Error", I2C_NUM_FDA801, *reg_val);
        }
#if 0
        res = i2c_write_wait(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr, &reg_addr, 1);
        if(res) {
            res = i2c_mcal_read(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr, reg_val, 1);
            if(false == res) {
#ifdef HAS_LOG
                LOG_ERROR(I2C, "Num:%u ReadRegErr Reg:0x%02X", I2C_NUM_FDA801, *reg_val);
#endif
            } else {
#ifdef HAS_LOG
                LOG_DEBUG(I2C, "Num:%u ReadRegOk Reg:0x%02X RegVal:0x%02X", I2C_NUM_FDA801, reg_addr, *reg_val);
#endif
            }
        } else {
#ifdef HAS_FDA801_DIAG
            LOG_ERROR(I2C, "%u SetRegAddrErr ChipAddr:0x%02x Reg:0x%02X=%s", I2C_NUM_FDA801, FdaConfNode->def_i2c_addr,
                      reg_addr, fda801_get_reg_name(reg_addr));
#endif
        }
#endif
#endif /*HAS_I2C*/
    } else {
#ifdef HAS_LOG
        LOG_ERROR(FDA801, "NodeErr");
#endif
    }
    return res;
}

bool fda801_write_reg(uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    const Fda801Config_t* FdaConfNode = Fda801GetConfNode(FDA801_MAIN);
    if(FdaConfNode) {
#ifdef HAS_I2C
        res = i2c_api_reg_write(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr, reg_addr, reg_val);
#if 0
        uint8_t frame[2] = {reg_addr, reg_val};
        res = i2c_write_wait(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr, &frame[0], 2);
#endif
        if(res) {
#ifdef HAS_LOG
            LOG_INFO(FDA801, "WriteOk Chip 0x%x Addr:%x Val:%x", FdaConfNode->def_i2c_addr, reg_addr, reg_val);
#endif
        } else {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "WriterErr Chip 0x%x Addr:%x Val:%x", FdaConfNode->def_i2c_addr, reg_addr, reg_val);
#endif
        }
#endif
    }
    return res;
}

bool fda801_write_lazy_reg(uint8_t reg_addr, uint8_t reg_val) {
    bool res = false;
    const Fda801Config_t* FdaConfNode = Fda801GetConfNode(FDA801_MAIN);
    Fda801Handle_t* Fda801Node = Fda801GetNode(FDA801_MAIN);
    if(FdaConfNode && Fda801Node) {
        uint8_t cur_reg_val = 0xFF;
        res = fda801_read_reg(reg_addr, &cur_reg_val);
        if(res) {
            if(cur_reg_val != reg_val) {
                res = fda801_write_reg(reg_addr, reg_val);
                Fda801Node->reg_val_disaccord++;
            }
        } else {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "RdErr");
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(FDA801, "NodeErr");
#endif
    }
    return res;
}

bool fda801_write_reg_by_bitmask(uint8_t reg_addr, char* bit_mask) {
    bool res = false;
    uint8_t cur_reg_val = 0xFF;
    res = fda801_read_reg(reg_addr, &cur_reg_val);
    if(res) {
        uint8_t new_reg_val = adjust_bits_u8(cur_reg_val, bit_mask);
        res = fda801_write_lazy_reg(reg_addr, new_reg_val);
        if(res) {
#ifdef HAS_LOG
            LOG_INFO(FDA801, "WrOk");
#endif
        } else {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "WrErr");
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(FDA801, "RdErr");
#endif
    }
    return res;
}

bool fda801_check(void) {
    bool res = false;
    const Fda801Config_t* FdaConfNode = Fda801GetConfNode(FDA801_MAIN);
    if(FdaConfNode) {
        res = i2c_check_addr(I2C_NUM_FDA801, FdaConfNode->def_i2c_addr);
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "I2C %u LinkLost Chip 0x%02x", I2C_NUM_FDA801, FdaConfNode->def_i2c_addr);
#endif
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(FDA801, "I2C %u LinkOk Chip 0x%02x", I2C_NUM_FDA801, FdaConfNode->def_i2c_addr);
#endif
        }
    }

    return res;
}

bool fda801_clock(bool on_off) {
    bool res = false;
#ifdef HAS_I2S
    Type64Union_t un64;
    un64.u32[0] = 0x00000000;
    un64.u32[1] = 0x00000000;
    if(on_off) {
        res = i2s_api_write(I2S_FDA801, (uint32_t*)&un64.u16[0], 2);
        if(res) {
            res = i2s_dma_stop(I2S_FDA801);
            if(false == res) {
#ifdef HAS_LOG
                LOG_ERROR(I2S, "StopErr");
#endif
            }
        } else {
            res = true;
#ifdef HAS_LOG
            LOG_ERROR(I2S, "WrErr");
#endif
        }
        if(res) {
            res = i2s_api_write(I2S_FDA801, (uint32_t*)&un64.u16[0], 2);
            if(false == res) {
#ifdef HAS_LOG
                LOG_ERROR(I2S, "WrErr");
#endif
            }
        }
    } else {
        res = i2s_dma_stop(I2S_FDA801);
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(I2S, "StopErr");
#endif
        }
    }
#endif /*HAS_I2S*/
    return res;
}

bool fda801_init(void) {
    bool res = false;
#ifdef HAS_SW_DAC
    size_t sample_size = sizeof(SampleType_t);
    if(4 != sample_size) {
        LOG_ERROR(FDA801, "DAC sample sizeErr %u byte", sample_size);
    }
#endif /*HAS_SW_DAC*/
#ifdef HAS_LOG
    res = set_log_level(FDA801, LOG_LEVEL_NOTICE);
    LOG_INFO(FDA801, "Init");
#endif
    const Fda801Config_t* FdaConfNode = Fda801GetConfNode(FDA801_MAIN);
    if(FdaConfNode) {
        res = fda801_set_chip_addr(FdaConfNode->def_i2c_addr);
        if(false == res) {
            LOG_ERROR(FDA801, "SetChipAddrErr 0x%02x", FdaConfNode->def_i2c_addr);
        } else {
#ifdef HAS_TIME
            delay_ms(600);
#endif
        }
    }
#ifdef HAS_I2S
    // res= fda801_clock(true);
#endif /*HAS_I2S*/
    if(res) {

        uint32_t i = 0;
        uint32_t success_cnt = 0;

        for(i = 0; i < FDA801_REG_CNT; i++) {
            res = fda801_write_reg(FdaConfNode->RegCfgDump[i].addr, FdaConfNode->RegCfgDump[i].val.reg_val);
            if(res) {
                success_cnt++;
            } else {
#ifdef HAS_LOG
                LOG_ERROR(FDA801, "%u WriteRegErr Reg:0x%02x Val: 0x%02x", i, FdaConfNode->RegCfgDump[i].addr,
                          FdaConfNode->RegCfgDump[i].val.reg_val);
#endif
            }
        }

        Fda801Handle_t* Fda801Node = Fda801GetNode(FDA801_MAIN);
        if(Fda801Node) {
            if(FDA801_REG_CNT == success_cnt) {
                res = true;
                Fda801Node->init = true;
            } else {
                res = false;
                Fda801Node->init = false;
            }
        }
    }
    return res;
}

bool fda801_reset(void) {
    bool res = false;
    return res;
}

static uint32_t DigitalInputFrameSyncFreq2Hz(uint8_t code) {
    uint32_t sample_rate = 0;
    switch(code) {
    case DIGITAL_INPUT_FRAME_SYN_FREQ_44_1_KHZ:
        sample_rate = 44100;
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_48_KHZ:
        sample_rate = 48000;
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_96_KHZ:
        sample_rate = 96000;
        break;
    case DIGITAL_INPUT_FRAME_SYN_FREQ_192_KHZ:
        sample_rate = 192000;
        break;
    default:
        sample_rate = 0;
        break;
    }
    return sample_rate;
}

uint32_t fda801_get_sample_rate(void) {
    uint32_t sample_rate = 0;
    Fda801RegInterface_t RegInterface;
    RegInterface.reg_val = 0;
    bool res = fda801_read_reg(REG_INTERFACE, &RegInterface.reg_val);
    if(res) {
        sample_rate = DigitalInputFrameSyncFreq2Hz(RegInterface.digital_input_settings);
    }
    return sample_rate;
}

Fda801ChannelState_t fda801_get_state(Fda801ChannelNum_t Channel) {
    bool res = true;
    Fda801ChannelState_t ChannelState = CH_STATE_UNDEF;
    uint8_t reg_addr = 0;
    switch(Channel) {
    case FDA_CHANNEL_1:
        reg_addr = REG_CHN1CNTR;
        res = true;
        break;
    case FDA_CHANNEL_2:
        reg_addr = REG_CHN2CNTR;
        res = true;
        break;
    case FDA_CHANNEL_3:
        reg_addr = REG_CHN3CNTR;
        res = true;
        break;
    case FDA_CHANNEL_4:
        reg_addr = REG_CHN4CNTR;
        res = true;
        break;
    default:
        res = false;
        break;
    }
    Fda801RegVal_t RegVal;
    if(res) {
        res = fda801_read_reg(reg_addr, &RegVal.reg_val);
    }
    if(res) {
        switch(Channel) {
        case FDA_CHANNEL_1:
            ChannelState = RegVal.Ib5AddrChannel1Ctrl.ch1_status;
            break;
        case FDA_CHANNEL_2:
            ChannelState = RegVal.Ib6AddrChannel2Ctrl.ch2_status;
            break;
        case FDA_CHANNEL_3:
            ChannelState = RegVal.Ib7AddrChannel3Ctrl.ch3_status;
            break;
        case FDA_CHANNEL_4:
            ChannelState = RegVal.Ib8AddrChannel4Ctrl.ch4_status;
            break;
        default:
            res = false;
            break;
        }
    }
    return ChannelState;
}

bool fda801_is_valid_gain(Fda801ChannelGain_t gain) {
    bool res = false;
    if((GAIN_SEL_GV1 <= gain) && (gain <= GAIN_SEL_GV4)) {
        res = true;
    }
    return res;
}

bool fda801_is_valid_channel(Fda801ChannelNum_t Channel) {
    bool res = false;
    if((FDA_CHANNEL_1 <= Channel) && (Channel <= FDA_CHANNEL_4)) {
        res = true;
    }
    return res;
}

bool fda801_set_state(Fda801ChannelNum_t Channel, Fda801ChannelState_t State) {
    bool res = false;
    Fda801RegVal_t RegVal;
    uint8_t chan_reg_addr = Channal2RegsLut[Channel - 1].RegAddr.ctrl;
    res = fda801_read_reg(chan_reg_addr, &RegVal.reg_val);
    if(res) {
        switch((uint8_t)Channel) {
        case FDA_CHANNEL_1:
            RegVal.Ib5AddrChannel1Ctrl.ch1_status = State;
            break;
        case FDA_CHANNEL_2:
            RegVal.Ib6AddrChannel2Ctrl.ch2_status = State;
            break;
        case FDA_CHANNEL_3:
            RegVal.Ib7AddrChannel3Ctrl.ch3_status = State;
            break;
        case FDA_CHANNEL_4:
            RegVal.Ib8AddrChannel4Ctrl.ch4_status = State;
            break;
        default:
            res = false;
            break;
        }
        res = fda801_write_lazy_reg(chan_reg_addr, RegVal.reg_val);
    }
    return res;
}

bool fda801_set_channel_play(Fda801ChannelNum_t Channel, bool on_off) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(FDA801, "Set Ch:%u Play %s", Channel, OnOffToStr(on_off));
#endif
    if(on_off) {
        res = fda801_set_channel_pwm(Channel, CH_PWM_ON);
        if(res) {
            res = fda801_set_state(Channel, CH_STATE_PLAY);
        }
    } else {
        res = fda801_set_channel_pwm(Channel, CH_PWM_OFF);
        if(res) {
            res = fda801_set_state(Channel, CH_STATE_MUTE);
        }
    }
    return res;
}

bool fda801_set_channel_pwm(Fda801ChannelNum_t Channel, Fda801ChannelPwm_t pwm_state) {
    bool res = false;
    Fda801RegVal_t RegVal;
    uint8_t chan_reg_addr = Channal2RegsLut[Channel - 1].RegAddr.ctrl;
    res = fda801_read_reg(chan_reg_addr, &RegVal.reg_val);
    if(res) {
        switch((uint8_t)Channel) {
        case FDA_CHANNEL_1:
            RegVal.Ib5AddrChannel1Ctrl.ch1_pwm = pwm_state;
            break;
        case FDA_CHANNEL_2:
            RegVal.Ib6AddrChannel2Ctrl.ch2_pwm = pwm_state;
            break;
        case FDA_CHANNEL_3:
            RegVal.Ib7AddrChannel3Ctrl.ch3_pwm = pwm_state;
            break;
        case FDA_CHANNEL_4:
            RegVal.Ib8AddrChannel4Ctrl.ch4_pwm = pwm_state;
            break;
        default:
            res = false;
            break;
        }
        res = fda801_write_lazy_reg(chan_reg_addr, RegVal.reg_val);
    }
    return res;
}

Fda801ChannelPwm_t fda801_get_channel_pwm(Fda801ChannelNum_t Channel) {
    bool res = false;
    Fda801ChannelPwm_t pwm_state = CH_PWM_UNDEF;
    res = fda801_is_valid_channel(Channel);
    if(res) {
        Fda801RegVal_t RegVal;
        uint8_t chan_reg_addr = Channal2RegsLut[Channel - 1].RegAddr.ctrl;
        res = fda801_read_reg(chan_reg_addr, &RegVal.reg_val);
        if(res) {
            switch((uint8_t)Channel) {
            case FDA_CHANNEL_1:
                pwm_state = RegVal.Ib5AddrChannel1Ctrl.ch1_pwm;
                break;
            case FDA_CHANNEL_2:
                pwm_state = RegVal.Ib6AddrChannel2Ctrl.ch2_pwm;
                break;
            case FDA_CHANNEL_3:
                pwm_state = RegVal.Ib7AddrChannel3Ctrl.ch3_pwm;
                break;
            case FDA_CHANNEL_4:
                pwm_state = RegVal.Ib8AddrChannel4Ctrl.ch4_pwm;
                break;
            default:
                res = false;
                break;
            }
        }
    }
    return pwm_state;
}

Fda801Channel_t* fda801_get_channel_node(Fda801ChannelNum_t Channel) {
    Fda801Channel_t* ChannelNode = NULL;
    Fda801Handle_t* Fda801Node = Fda801GetNode(FDA801_MAIN);
    if(Fda801Node) {
        bool res = fda801_is_valid_channel(Channel);
        if(res) {
            ChannelNode = &Fda801Node->Channel[Channel - 1];
        }
    }
    return ChannelNode;
}

bool fda801_channel_dc_diag_start(Fda801ChannelNum_t Channel) {
    bool res = false;
    res = fda801_set_state(Channel, CH_STATE_MUTE);

    Fda801Channel_t* ChannelNode = fda801_get_channel_node(Channel);
    if(ChannelNode) {
        ChannelNode->DcDiag = DC_DIAG_UNDEF;
        ChannelNode->DcOutput.byte = 0;
    }

    Fda801RegVal_t RegVal;
    res = fda801_read_reg(Channal2RegsLut[Channel - 1].RegAddr.ctrl, &RegVal.reg_val);
    if(res) {
        switch((uint8_t)Channel) {
        case FDA_CHANNEL_1:
            RegVal.Ib5AddrChannel1Ctrl.ch1_status = CH_STATE_MUTE;
            RegVal.Ib5AddrChannel1Ctrl.ch1_dc_diag = CH_AC_DC_DIAG_START;
            RegVal.Ib5AddrChannel1Ctrl.ch1_pwm = SW_ON;
            break;
        case FDA_CHANNEL_2:
            RegVal.Ib6AddrChannel2Ctrl.ch2_status = CH_STATE_MUTE;
            RegVal.Ib6AddrChannel2Ctrl.ch2_dc_diag = CH_AC_DC_DIAG_START;
            RegVal.Ib6AddrChannel2Ctrl.ch2_pwm = SW_ON;
            break;
        case FDA_CHANNEL_3:
            RegVal.Ib7AddrChannel3Ctrl.ch3_status = CH_STATE_MUTE;
            RegVal.Ib7AddrChannel3Ctrl.ch3_dc_diag = CH_AC_DC_DIAG_START;
            RegVal.Ib7AddrChannel3Ctrl.ch3_pwm = SW_ON;
            break;
        case FDA_CHANNEL_4:
            RegVal.Ib8AddrChannel4Ctrl.ch4_status = CH_STATE_MUTE;
            RegVal.Ib8AddrChannel4Ctrl.ch4_dc_diag = CH_AC_DC_DIAG_START;
            RegVal.Ib8AddrChannel4Ctrl.ch4_pwm = SW_ON;
            break;
        default:
            res = false;
            break;
        }
        res = fda801_write_reg(Channal2RegsLut[Channel - 1].RegAddr.ctrl, RegVal.reg_val);
    }

    return res;
}

bool fda801_watchdog_set(bool on) {
    Fda801RegIb13Addr_t Reg;
    Reg.reg_val = 0;
    bool res = fda801_read_reg(REG_DIGITAL, &Reg.reg_val);
    if(res) {
        if(on) {
            Reg.watchdog_on_i2sws_signal = I2S_WS_WATCHDOG_ENABLE;
        } else {
            Reg.watchdog_on_i2sws_signal = I2S_WS_WATCHDOG_DISABLE;
        }
        res = fda801_write_lazy_reg(REG_DIGITAL, Reg.reg_val);
    }
    return res;
}

bool fda801_watchdog_get(void) {
    Fda801RegIb13Addr_t Reg;
    Reg.reg_val = 0;
    bool res = fda801_read_reg(REG_DIGITAL, &Reg.reg_val);
    if(res) {
        if(I2S_WS_WATCHDOG_ENABLE == Reg.watchdog_on_i2sws_signal) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

bool fda801_set_channel_gain(Fda801ChannelNum_t channel, Fda801ChannelGain_t gain) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(FDA801, "SetChan %u Gain %u", channel, gain);
#endif
    res = fda801_is_valid_gain(gain);
    if(res) {
        const Channal2Regs_t* Channal2Regs = fda801_get_chan_regs(channel);
        Fda801RegChannelCtrl_t RegChannelCtrl;
        RegChannelCtrl.reg_val = 0;
        if(Channal2Regs) {
            res = fda801_read_reg(Channal2Regs->RegAddr.ctrl, &RegChannelCtrl.reg_val);
            RegChannelCtrl.chx_gain_sel = gain;
            res = fda801_write_lazy_reg(Channal2Regs->RegAddr.ctrl, RegChannelCtrl.reg_val);
        } else {
#ifdef HAS_LOG
            LOG_ERROR(FDA801, "Chan %u Err", channel);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(FDA801, "Gain %u Err", gain);
#endif
    }
    return res;
}

bool fda801_get_channel_gain(Fda801ChannelNum_t channel, Fda801ChannelGain_t* Gain) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(FDA801, "GetChan %u Gain", channel);
#endif

    const Channal2Regs_t* Channal2Regs = fda801_get_chan_regs(channel);
    Fda801RegChannelCtrl_t RegChannelCtrl;
    RegChannelCtrl.reg_val = 0;
    if(Channal2Regs) {
        res = fda801_read_reg(Channal2Regs->RegAddr.ctrl, &RegChannelCtrl.reg_val);
    }
    if(res && Gain) {
        (*Gain) = (Fda801ChannelGain_t)RegChannelCtrl.chx_gain_sel;
    }
    return res;
}
