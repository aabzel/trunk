#include "nau8814_drv.h"

#include <float.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "bit_const.h"
#include "bit_utils.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "data_utils.h"
#include "log.h"
#include "none_blocking_pause.h"

#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_mcal.h"
#endif

COMPONENT_GET_NODE(Nau8814, nau8814)
COMPONENT_GET_CONFIG(Nau8814, nau8814)

uint8_t nau8814_compose_register_address(uint8_t const register_address) {
    uint8_t addr_val = register_address;
    addr_val = addr_val << 1;
    RESET_BIT_NUM(addr_val, 0);
    return addr_val;
}

const Nau8814RegInfo_t Nau8814RegInfo[] = {
    {
        .valid = true,
        .addr = NAU8814_REG_SOFTWARE_RESET,
        .name = "SOFTWARE_RESET",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_POWER_MANAGEMENT_1,
        .name = "POWER_MANAGEMENT_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_POWER_MANAGEMENT_2,
        .name = "POWER_MANAGEMENT_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_POWER_MANAGEMENT_3,
        .name = "POWER_MANAGEMENT_3",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_AUDIO_INTERFACE,
        .name = "AUDIO_INTERFACE",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_COMPANDING,
        .name = "COMPANDING ",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_CLOCK_CONTROL_1,
        .name = "CLOCK_CONTROL_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_CLOCK_CONTROL_2,
        .name = "CLOCK_CONTROL_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_GPIO_CTRL,
        .name = "GPIO_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_DAC_CTRL,
        .name = "DAC_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_DAC_VOLUME,
        .name = "DAC_VOLUME",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADC_CTRL,
        .name = "ADC_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADC_VOLUME,
        .name = "ADC_VOLUME",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_EQ1_LOW_CUTOFF,
        .name = "EQ1_LOW_CUTOFF",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_EQ2_PEAK_1,
        .name = "EQ2_PEAK_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_EQ3_PEAK_2,
        .name = "EQ3_PEAK_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_EQ4_PEAK_3,
        .name = "EQ4_PEAK3",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_EQ5_HIGH_CUTOFF,
        .name = "EQ5_HIGH_CUTOFF",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_DAC_LIMITER_1,
        .name = "DAC_LIMITER_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_DAC_LIMITER_2,
        .name = "DAC_LIMITER_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_NOTCH_FILTER_0_HIGH,
        .name = "NOTCH_FILTER_0_HIGH",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_NOTCH_FILTER_0_LOW,
        .name = "NOTCH_FILTER_0_LOW",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_NOTCH_FILTER_1_HIGH,
        .name = "NOTCH_FILTER_1_HIGH",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_NOTCH_FILTER_1_LOW,
        .name = "NOTCH_FILTER_1_LOW ",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ALC_CTRL_1,
        .name = "ALC_CTRL_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ALC_CTRL_2,
        .name = "ALC_CTRL_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ALC_CTRL_3,
        .name = "ALC_CTRL_3",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_NOISE_GATE,
        .name = "NOISE_GATE",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_PLL_N_CTRL,
        .name = "PLL_N_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_PLL_K_1,
        .name = "PLL_K_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_PLL_K_2,
        .name = "PLL_K_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_PLL_K_3,
        .name = "PLL_K_3",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ATTENUATION_CTRL,
        .name = "ATTENUATION_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_INPUT_CTRL,
        .name = "INPUT_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_PGA_GAIN,
        .name = "PGA_GAIN",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADC_BOOST,
        .name = "ADC_BOOST",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_OUTPUT_CTRL,
        .name = "OUTPUT_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_SPEAKER_MIXER_CTRL,
        .name = "SPEAKER_MIXER_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_SPKOUT_VOLUME,
        .name = "SPKOUT_VOLUME",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_MONO_MIXER_CONTROL,
        .name = "MIXER_CONTROL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_POWER_MANAGEMENT_4,
        .name = "POWER_MANAGEMENT_4",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_TIME_SLOT,
        .name = "TIME_SLOT",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADCOUT_DRIVE,
        .name = "ADCOUT_DRIVE",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_SILICON_REVISION,
        .name = "SILICON_REVISION",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_2_WIRE_ID,
        .name = "2_WIRE_ID",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADDITIONAL_ID,
        .name = "ADDITIONAL_ID",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_RESERVED,
        .name = "RESERVED",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_HIGH_VOLTAGE_CTRL,
        .name = "HIGH_VOLTAGE_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ALC_ENHANCEMENTS_1,
        .name = "ALC_ENHANCEMENTS_1",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ALC_ENHANCEMENTS_2,
        .name = "ALC_ENHANCEMENTS_2",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_ADDITIONAL_IF_CTRL,
        .name = "ADDITIONAL_IF_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_POWER_TIE_OFF_CTRL,
        .name = "POWER_TIE_OFF_CTRL",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_AGC_P2P_DETECTOR,
        .name = "AGC_P2P_DETECTOR",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_AGC_PEAK_DETECTOR,
        .name = "AGC_PEAK_DETECTOR",
        .access = ACCESS_READ_ONLY,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_CONTROL_AND_STATUS,
        .name = "CONTROL_AND_STATUS",
        .access = ACCESS_READ_WRITE,
    },
    {
        .valid = true,
        .addr = NAU8814_REG_OUTPUT_TIE_OFF_CTRL,
        .name = "OUTPUT_TIE_OFF_CTRL",
        .access = ACCESS_READ_WRITE,
    },
};

uint16_t nau8814_make_frame(Nau8814RegAddr_t addr, uint16_t reg_value) {
    Nau8814WriteFrame_t Frame;
    Frame.word = 0;
    Frame.reg_addr = WORD_MASK_7BIT & addr;
    Frame.reg_value = WORD_MASK_9BIT & reg_value;
    Frame.word = reverse_byte_order_uint16(Frame.word);
    return Frame.word;
}

NauPllN_t NauPllNToCode(uint8_t plln) {
    NauPllN_t code = 1;
    switch(plln) {
    case 5:
        code = PLLN_5;
        break;
    case 6:
        code = PLLN_6;
        break;
    case 7:
        code = PLLN_7;
        break;
    case 8:
        code = PLLN_8;
        break;
    case 9:
        code = PLLN_9;
        break;
    case 10:
        code = PLLN_10;
        break;
    case 11:
        code = PLLN_11;
        break;
    case 12:
        code = PLLN_12;
        break;
    case 13:
        code = PLLN_13;
        break;
    default:
        code = PLLN_NOT_VALID_0;
        LOG_ERROR(NAU8814, "Invalid PLLN %u", plln);
        break;
    }
    return code;
}

uint32_t nau8814_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(Nau8814RegInfo);
    return cnt;
}

bool nau8814_reg_read_ll(Nau8814Handle_t* Node, Nau8814RegAddr_t addr, uint16_t* const word) {
    bool res = false;
    if(Node) {
        if(word) {
            LOG_DEBUG(NAU8814, "Read,Chip:0x%x,Reg:0x%02x", Node->chip_addr, addr);
#if 1
            uint16_t reg_word = 0;
            uint8_t addr_val = nau8814_compose_register_address(addr);
            LOG_DEBUG(NAU8814, "Addr:0x%02x,AddrVal:0x%02x", addr, addr_val);
            res = i2c_api_read_word(Node->i2c_num, Node->chip_addr, addr_val, &reg_word);
            if(res) {
                *word = reg_word;
                LOG_PARN(NAU8814, "ReadMemOk,Reg:0x%02x,Val:0x%04x", addr, reg_word);
            } else {
                LOG_ERROR(NAU8814, "I2C%u,ReadWordErr,Reg:0x%02x=%s", Node->i2c_num, addr, Nau8814RegAddrToName(addr));
            }
#endif /*HAS_I2C*/

#if 0

            uint8_t addr_val =  nau8814_compose_register_address(addr);
            uint16_t reg_word = 0;
            LOG_DEBUG(NAU8814, "Addr:0x%02x,AddrVal:0x%02x", addr, addr_val);
            res = i2c_api_read_mem(Node->i2c_num, Node->chip_addr, &addr_val, 1, (uint8_t*)&reg_word, 2);
            if(res) {
                *word = reverse_byte_order_uint16(reg_word);
                LOG_PARN(NAU8814, "ReadMemOk,Reg:0x%02x,Val:0x%04x", addr, reg_word);
            } else {
                LOG_ERROR(NAU8814, "I2C%u,ReadMemErr,Reg:0x%02x=%s", Node->i2c_num, addr, Nau8814RegAddrToName(addr));
            }
#endif /*HAS_I2C*/
        }
    }
    return res;
}

/*
bool i2c_api_read_word(uint8_t num, uint8_t chip_addr, uint8_t word_addr, uint16_t* const word) {
    bool res = false;
    uint16_t reg_word = 0;
    LOG_DEBUG(I2C, "I2C%u,Chip:0x%02x,Addr:0x%02x", num, chip_addr, word_addr);
    res = i2c_api_read_mem(num, chip_addr, &word_addr, 1, (uint8_t*)&reg_word, 2);
    if(res) {
        *word = reverse_byte_order_uint16(reg_word);
        LOG_PARN(I2C, "ReadMemOk,Reg:0x%02x,Word:0x%04x", word_addr, reg_word);
    } else {
        LOG_ERROR(I2C, "I2C%u,Read,Word,Err,Reg:0x%02x", num, word_addr);
    }
    return res;
}*/

uint8_t NauPllNcodeToValue(NauPllN_t code) {
    uint8_t value = 0;
    switch((uint8_t)code) {
    case PLLN_NOT_VALID_0:
        value = 0;
        break;
    case PLLN_NOT_VALID_1:
        value = 0;
        break;
    case PLLN_NOT_VALID_2:
        value = 0;
        break;
    case PLLN_NOT_VALID_3:
        value = 0;
        break;
    case PLLN_NOT_VALID_4:
        value = 0;
        break;
    case PLLN_5:
        value = 5;
        break;
    case PLLN_6:
        value = 6;
        break;
    case PLLN_7:
        value = 7;
        break;
    case PLLN_8:
        value = 8;
        break;
    case PLLN_9:
        value = 9;
        break;
    case PLLN_10:
        value = 10;
        break;
    case PLLN_11:
        value = 11;
        break;
    case PLLN_12:
        value = 12;
        break;
    case PLLN_13:
        value = 13;
        break;
    case PLLN_NOT_VALID_14:
        value = 0;
        break;
    case PLLN_NOT_VALID_15:
        value = 0;
        break;
    }
    return value;
}

double NauMasterClockSelectionToValue(NauMclkSel_t code) {
    uint8_t divider = 0;
    switch((uint8_t)code) {
    case MCLKSEL_DIV1:
        divider = 1.0;
        break;
    case MCLKSEL_DIV1_5:
        divider = 1.5;
        break;
    case MCLKSEL_DIV2:
        divider = 2.0;
        break;
    case MCLKSEL_DIV3:
        divider = 3.0;
        break;
    case MCLKSEL_DIV4:
        divider = 4.0;
        break;
    case MCLKSEL_DIV6:
        divider = 6.0;
        break;
    case MCLKSEL_DIV8:
        divider = 8.0;
        break;
    case MCLKSEL_DIV12:
        divider = 12.0;
        break;
    }
    return divider;
}

uint8_t NauPllDcodeToValue(NauPllMclk_t d_code) {
    uint8_t pll_d = 0;
    switch((uint8_t)d_code) {
    case PLLMCLK_MCLK_DIV1:
        pll_d = 1;
        break;
    case PLLMCLK_MCLK_DIV2:
        pll_d = 2;
        break;
    }
    return pll_d;
}

bool nau8814_reg_read_all(uint8_t num) {
    bool res = false;
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        uint8_t i = 0;
        uint8_t ok_cnt = 0;
        for(i = 0; i < NAU8814_REG_CNT; i++) {
            // res = nau8814_reg_read(Nau8814RegVal[i].addr, &Nau8814RegVal[i].value.byte);
            if(res) {
                ok_cnt++;
            } else {
                // LOG_ERROR(I2C, "Read Reg:0x%02x Err", Nau8814RegVal[i].addr);
            }
        }

        if(ok_cnt == NAU8814_REG_CNT) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

static bool nau8814_is_connected_ll(Nau8814Handle_t* Node) {
    bool res = false;
    if(Node) {
        uint16_t word = 0;
        res = nau8814_reg_read_ll(Node, NAU8814_REG_2_WIRE_ID, &word);
        if(res) {
            if(0x001a == word) {
                res = true;
            } else {
                LOG_ERROR(NAU8814, "SiRevErr:0x%04x", word);
                res = false;
            }
        } else {
            LOG_ERROR(NAU8814, "ReadIDErr");
            res = false;
        }
    }
    return res;
}

bool nau8814_is_connected(uint8_t num) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_is_connected_ll(Node);
    }
    return res;
}

bool nau8814_reg_write_ll(Nau8814Handle_t* Node, Nau8814RegAddr_t addr, uint16_t reg_value) {
    bool res = false;
    if(Node) {
        uint16_t tx_word = nau8814_make_frame(addr, reg_value);
        LOG_DEBUG(NAU8814, "Set,Reg:0x%02x=%s,Val:0x%04x,TxWord:0x%04x", addr, Nau8814RegAddrToName(addr), reg_value,
                  tx_word);
#ifdef HAS_I2C
        res = i2c_write_word(Node->i2c_num, Node->chip_addr, tx_word);
        if(res) {
            LOG_DEBUG(NAU8814, "WrOk!Addr:0x%02x,Val:0x%s", addr, ArrayToStr((uint8_t*)&tx_word, 2));
        } else {
            LOG_ERROR(NAU8814, "SetErr,Addr:0x%02x=%s,Val:0x%04x", addr, Nau8814RegAddrToName(addr), tx_word);
        }
#endif /*HAS_I2C*/
    } else {
        LOG_ERROR(NAU8814, "NodeErr");
    }
    return res;
}

/*Figure 9. Writing One Byte of Data to the NAU8814*/
bool nau8814_reg_write(uint8_t num, Nau8814RegAddr_t addr, uint16_t word) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_reg_write_ll(Node, addr, word);
    } else {
        LOG_ERROR(NAU8814, "%u", num);
    }
    return res;
}

bool nau8814_reg_write_verify(uint8_t num, Nau8814RegAddr_t addr, uint16_t set_word) {
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(NAU8814, "SetVerify Reg:0x%02x Val:0x%02x", addr, set_word);
    res = nau8814_reg_write(num, addr, set_word);
    if(res) {
        uint16_t word_read = 0;
        res = nau8814_reg_read(num, addr, &word_read);
        if(word_read == set_word) {
            res = true;
            LOG_INFO(NAU8814, "SetVerify Reg:0x%02x Val:0x%02x Ok", addr, set_word);
        } else {
            LOG_ERROR(NAU8814, "VerifyErr Reg:0x%02x Set:0x%02x != Get:0x%02x", addr, set_word, word_read);
            res = false;
        }
    }

    return res;
}

bool nau8814_reset(uint8_t num) {
    bool res = false;

    return res;
}

bool nau8814_is_valid_addr(uint8_t addr) {
    bool res = false;
    const Nau8814RegInfo_t* Node = Nau8814RegAddrToInfo(addr);
    if(Node) {
        res = true;
    }

    return res;
}

bool nau8814_reg_read(uint8_t num, Nau8814RegAddr_t addr, uint16_t* const word) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        LOG_DEBUG(NAU8814, "Read Chip:0x%x,Reg:0x%02x", Node->chip_addr, addr);
        res = nau8814_reg_read_ll(Node, addr, word);
        if(res) {
            LOG_PARN(NAU8814, "ReadOk,Reg:0x%02x,Val:0x%04x", addr, *word);
        } else {
            LOG_ERROR(NAU8814, "ReadErr,Reg:0x%02x=%s", addr, Nau8814RegAddrToName(addr));
        }
    }
    return res;
}

bool nau8814_init_custom(void) {
    log_level_get_set(NAU8814, LOG_LEVEL_INFO);
    return true;
}

static bool nau8814_register_config(uint8_t num, const Nau8814RegVal_t* const Reg, uint32_t cnt) {
    bool res = false;
    if(Reg) {
        if(cnt) {
            uint32_t i = 0;
            uint32_t ok = 0;
            for(i = 0; i < cnt; i++) {
                res = nau8814_reg_write(num, Reg[i].addr, Reg[i].Reg.word);
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

static bool nau8814_init_common(const Nau8814Config_t* Config, Nau8814Handle_t* Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->chip_addr = Config->chip_addr;
            Node->p_mic_gain = Config->p_mic_gain;
            Node->aux_gain = Config->aux_gain;
            Node->dac_gain = Config->dac_gain;
            Node->pll_k = Config->pll_k;
            Node->pga_gain = Config->pga_gain;
            Node->i2c_num = Config->i2c_num;
            Node->i2s_role = Config->i2s_role;
            Node->i2s_num = Config->i2s_num;
            Node->adc_on = Config->adc_on;
            Node->dac_num = Config->dac_num;
            res = true;
        }
    }
    return res;
}

bool nau8814_pll_init(uint8_t num) {
    bool res = false;
    LOG_WARNING(NAU8814, "InitPLL");
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            res = nau8814_pll_n_set(num, Config->pll_n);

            res = nau8814_pll_k_get(num, &Node->pll_k);
            if(res) {
                LOG_INFO(NAU8814, "PLL,K:%u=0x%08x", Node->pll_k, Node->pll_k);
            } else {
                LOG_ERROR(NAU8814, "PllErr");
            }
        }
    }
    return res;
}

bool nau8814_init_one(uint8_t num) {
    bool res = false;
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        LOG_WARNING(NAU8814, "Init:%s", Nau8814ConfigToStr(Config));
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            res = nau8814_init_common(Config, Node);
            Node->valid = true;

            log_level_get_set(I2C, LOG_LEVEL_INFO);
            log_level_get_set(NAU8814, LOG_LEVEL_INFO);

            res = nau8814_is_connected_ll(Node);
            if(res) {
                res = nau8814_register_config(num, Config->RegVals, Config->reg_val_cnt);

                res = nau8814_pll_init(num) && res;
                res = nau8814_i2s_role_set(num, Config->i2s_role) && res;

            } else {
                LOG_ERROR(NAU8814, "LinkErr");
            }

#if HAS_NAU8814_ADC
            res = nau8814_init_adc(num) && res;
#endif

#if HAS_NAU8814_DAC
            res = nau8814_init_dac(num) && res;
#endif

            log_level_get_set(I2C, LOG_LEVEL_INFO);
            log_level_get_set(NAU8814, LOG_LEVEL_NOTICE);

            if(res) {
                Node->init = true;
            }
        } else {
            LOG_ERROR(NAU8814, "NodeErr");
        }
    }
    return res;
}

const Nau8814RegInfo_t* Nau8814RegAddrToInfo(Nau8814RegAddr_t addr) {
    Nau8814RegInfo_t* Info = NULL;
    uint32_t cnt = ARRAY_SIZE(Nau8814RegInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(Nau8814RegInfo[i].valid) {
            if(addr == Nau8814RegInfo[i].addr) {
                Info = &Nau8814RegInfo[i];
            }
        }
    }
    return Info;
}

bool nau8814_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(NAU8814, "Proc:%u", num);
    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            if(Node->init) {
#if 0
                LOG_DEBUG(NAU8814, "%u I2cLinkOk", num);
                uint16_t word = 0;
                res = nau8814_reg_read_ll(Node, NAU8814_REG_AGC_P2P_DETECTOR, &word);
                if(res) {
                    LOG_DEBUG(NAU8814, "Amp:%u", word);
                }

                res = nau8814_reg_read_ll(Node, NAU8814_REG_AGC_PEAK_DETECTOR, &word);
                if(res) {
                    LOG_DEBUG(NAU8814, "Amp:%u", word);
                }
#endif
            } else {
                LOG_WARNING(NAU8814, "%u InitErr", num);
            }
        } else {
            LOG_ERROR(NAU8814, "NodeErr %u", num);
        }
    }
    return res;
}

static IfBusRole_t NauClkIoEnToBusRole(NauClkIoEn_t code) {
    IfBusRole_t bus_role = 0;
    switch((uint8_t)code) {
    case CLKIOEN_SLAVE_MODE:
        bus_role = IF_BUS_ROLE_SLAVE;
        break;
    case CLKIOEN_MASTER_MODE:
        bus_role = IF_BUS_ROLE_MASTER;
        break;
    }
    return bus_role;
}

bool nau8814_i2s_role_get(uint8_t num, IfBusRole_t* const i2s_role) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        *i2s_role = IF_BUS_ROLE_UNDEF;
        Nau8814RegClockControl1_t Reg;
        Reg.word = 0;
        res = nau8814_reg_read_ll(Node, NAU8814_REG_CLOCK_CONTROL_1, &Reg.word);
        if(res) {
            *i2s_role = NauClkIoEnToBusRole(Reg.clkioen);
        }
    }
    return res;
}

static NauClkIoEn_t BusRoleToClkIoEn(IfBusRole_t i2s_role) {
    NauClkIoEn_t code = CLKIOEN_UNDEF;
    switch((uint8_t)i2s_role) {
    case IF_BUS_ROLE_MASTER:
        code = CLKIOEN_MASTER_MODE;
        break;
    case IF_BUS_ROLE_SLAVE:
        code = CLKIOEN_SLAVE_MODE;
        break;
    }
    return code;
}

bool nau8814_i2s_role_set(uint8_t num, IfBusRole_t i2s_role) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        Nau8814RegClockControl1_t Reg;
        Reg.word = 0;
        res = nau8814_reg_read_ll(Node, NAU8814_REG_CLOCK_CONTROL_1, &Reg.word);
        if(res) {
            Reg.clkioen = BusRoleToClkIoEn(i2s_role);
            res = nau8814_reg_write_ll(Node, NAU8814_REG_CLOCK_CONTROL_1, Reg.word);
        }
    }
    return res;
}

bool nau8814_pll_n_set(uint8_t num, uint8_t plln) {
    bool res = false;
    Nau8814RegPllNControl_t Reg;
    Reg.word = 0;
    res = nau8814_reg_read(num, NAU8814_REG_PLL_N_CTRL, &Reg.word);
    if(res) {
        Reg.plln = NauPllNToCode(plln);
        LOG_WARNING(NAU8814, "Set PLLN:%u->code:%u", plln, Reg.plln);
        res = nau8814_reg_write(num, NAU8814_REG_PLL_N_CTRL, Reg.word);
    }
    return res;
}

bool nau8814_pll_k_get(uint8_t num, uint32_t* const pll_k) {
    bool res = false;
    if(pll_k) {
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            Nau8814Pllk_t Pllk;
            Pllk.pll_k = 0;

            Nau8814RegPllkl_t Reg1;
            Reg1.word = 0;

            Nau8814RegPllk2_t Reg2;
            Reg2.word = 0;

            Nau8814RegPllk3_t Reg3;
            Reg3.word = 0;

            res = nau8814_reg_read_ll(Node, NAU8814_REG_PLL_K_1, &Reg1.word);
            res = nau8814_reg_read_ll(Node, NAU8814_REG_PLL_K_2, &Reg2.word) && res;
            res = nau8814_reg_read_ll(Node, NAU8814_REG_PLL_K_3, &Reg3.word) && res;
            if(res) {
                Pllk.pll_k_8_0 = Reg3.pllk_8_0;
                Pllk.pll_k_17_9 = Reg2.pllk_17_9;
                Pllk.pll_k_23_18 = Reg1.pllk_23_18;
                LOG_INFO(NAU8814, "%u,PLL_K:%u", num, Pllk.pll_k);
                Node->pll_k = Pllk.pll_k;
                *pll_k = Pllk.pll_k;
            }
        }
    }
    return res;
}

bool nau8814_pll_k_set(uint8_t num, uint32_t set_pll_k) {
    bool res = false;
    uint32_t get_pll_k = 0;
    res = nau8814_pll_k_get(num, &get_pll_k);
    if(res) {
        if(get_pll_k == set_pll_k) {
            LOG_INFO(NAU8814, "%u, AlreadySame,PLL_K:%u", num, get_pll_k);
        } else {
            Nau8814Pllk_t Pllk;
            Pllk.pll_k = set_pll_k;

            Nau8814RegPllkl_t Reg1;
            Reg1.word = 0;
            Reg1.pllk_23_18 = Pllk.pll_k_23_18;

            Nau8814RegPllk2_t Reg2;
            Reg2.word = 0;
            Reg2.pllk_17_9 = Pllk.pll_k_17_9;

            Nau8814RegPllk3_t Reg3;
            Reg3.word = 0;
            Pllk.pll_k_8_0 = Reg3.pllk_8_0;

            Nau8814Handle_t* Node = Nau8814GetNode(num);
            if(Node) {
                res = nau8814_reg_write_ll(Node, NAU8814_REG_PLL_K_1, Reg1.word);
                res = nau8814_reg_write_ll(Node, NAU8814_REG_PLL_K_2, Reg2.word) && res;
                res = nau8814_reg_write_ll(Node, NAU8814_REG_PLL_K_3, Reg3.word) && res;
            }
        }
    }
    return res;
}

// see Master Clock Selection
static const Nau8814MasterClockSelInfo_t MasterClockSelInfo[] = {
    {
        .mclksel = 0,
        .divider = 1.0,
    },
    {
        .mclksel = 1,
        .divider = 1.5,
    },
    {
        .mclksel = 2,
        .divider = 2.0,
    },
    {
        .mclksel = 3,
        .divider = 3.0,
    },
    {
        .mclksel = 4,
        .divider = 4.0,
    },
    {
        .mclksel = 5,
        .divider = 6.0,
    },
    {
        .mclksel = 6,
        .divider = 8.0,
    },
    {
        .mclksel = 7,
        .divider = 12.0,
    },
};

/*
  see 12.8. CLOCK GENERATION BLOCK
  Table 25: Registers associated with PLL
  F1 = (MCLK / D)
  f2 = (4 * P * IMCLK)
  f_pll = f2/4
  f2 = R * F1
  R = f2 / f1 = xy.abcdefgh decimal value
  N = xy
  K = (2^24) * (0.abcdefgh)
  IMCLK = (256) * (desired codec sample rate)
 */
bool nau8814_calc_pll(uint32_t mclk_hz, uint32_t fs_hz, uint32_t k_step) {
    bool res = false;
    LOG_INFO(NAU8814, "CalcPll,MCLK:%u Hz,FS:%u Hz,Kstep:%u", mclk_hz, fs_hz, k_step);
    Nau8814PllInfo_t PllInfo = {0};
    float calc_fs_hz = 0.0;
    float diff_fs_hz = 0.0;
    float min_err_fs_hz = FLT_MAX;
    PllInfo.mclk_hz = mclk_hz;
    PllInfo.fs_hz = fs_hz;
    uint32_t i = 0;
    uint32_t D = 0; // PLLMCLK PLL Clock
    uint32_t N = 0; // PLLN
    uint32_t K = 0; // PLLK
    uint32_t P = 0; // MCLKSEL
    for(D = 1; D <= 2; D++) {
        for(N = 5; N <= 13; N++) {
            for(K = 0; K <= 0x00FFFFFF; K += k_step) {
                for(P = 0; P < ARRAY_SIZE(MasterClockSelInfo); P++) {
                    PllInfo.f_1 = ((float)PllInfo.mclk_hz) / ((float)D);

                    PllInfo.fraction = ((float)K) / ((float)0x1000000);
                    PllInfo.R = ((float)N) + PllInfo.fraction;
                    PllInfo.f_2 = PllInfo.R * PllInfo.f_1;
                    PllInfo.f_pll = PllInfo.f_2 / 4.0;
                    PllInfo.i_mclk = PllInfo.f_pll / ((float)MasterClockSelInfo[P].divider);
                    calc_fs_hz = PllInfo.i_mclk / 256.0;
                    diff_fs_hz = fabsf(calc_fs_hz - ((float)fs_hz));
                    if(diff_fs_hz < min_err_fs_hz) {
                        i++;
                        min_err_fs_hz = diff_fs_hz;
                        PllInfo.N = N;
                        PllInfo.K = K;
                        PllInfo.D = D;
                        cli_printf("\r%u,%s", i, Nau8814PllInfoToStr(&PllInfo));
                        res = true;
                    }
                }
            }
        }
    }
    cli_printf(CRLF);
    return res;
}

bool nau8814_pll_n_get(uint8_t num, uint8_t* const pll_n) {
    bool res = false;

    Nau8814RegPllNControl_t Reg;
    Reg.word = 0;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_reg_read_ll(Node, NAU8814_REG_PLL_N_CTRL, &Reg.word);
        if(res) {
            Node->pll_n = NauPllNcodeToValue(Reg.plln);
            LOG_NOTICE(NAU8814, "Get:PLL,Code:%u->N:%u", Reg.plln, Node->pll_n);
            *pll_n = Node->pll_n;
        }
    }

    return res;
}

bool nau8814_pll_d_get(uint8_t num, uint8_t* const pll_d) {
    bool res = false;
    Nau8814RegPllNControl_t Reg;
    Reg.word = 0;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        res = nau8814_reg_read_ll(Node, NAU8814_REG_PLL_N_CTRL, &Reg.word);
        if(res) {
            Node->pll_d = NauPllDcodeToValue(Reg.pllmclk);
            *pll_d = Node->pll_d;
        }
    }

    return res;
}

bool nau8814_master_clock_div_get(uint8_t num, double* const divider) {
    bool res = false;
    Nau8814Handle_t* Node = Nau8814GetNode(num);
    if(Node) {
        Nau8814RegClockControl1_t Reg;
        Reg.word = 0;
        res = nau8814_reg_read_ll(Node, NAU8814_REG_CLOCK_CONTROL_1, &Reg.word);
        if(res) {
            *divider = NauMasterClockSelectionToValue(Reg.mclksel);
        }
    }

    return res;
}

COMPONENT_INIT_PATTERT(NAU8814, NAU8814, nau8814)
COMPONENT_PROC_PATTERT(NAU8814, NAU8814, nau8814)
