#include "max9860_drv.h"

#include <string.h>

#include "byte_utils.h"
#include "data_utils.h"
#include "log.h"
#include "max9860_config.h"
#include "max9860_dep.h"
#include "max9860_diag.h"
#include "none_blocking_pause.h"
#ifdef HAS_I2C
#include "i2c_mcal.h"
#endif

#ifdef HAS_I2S
#include "i2s_diag.h"
#include "i2s_drv.h"
#endif

const Max9860RegName_t RegNameLUT[] = {
    {
        /*1*/
        .addr = MAX9860_REG_INTERRUPT_STATUS,
        .name = "IntStat",
    },
    {
        /*2*/
        .addr = MAX9860_REG_MICROPHONE_NG_AGC_READBACK,
        .name = "MicNGAgccRead",
    },
    {
        /*3*/
        .addr = MAX9860_REG_INTERRUPT_ENABLE,
        .name = "IntEn",
    },
    {
        /*4*/
        .addr = MAX9860_REG_SYSTEM_CLOCK,
        .name = "SysClock",
    },
    {
        /*5*/
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH,
        .name = "StereoAudioClkCtrlHi",
    },
    {
        /*6*/
        .addr = MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW,
        .name = "StereoAudioClkCtrlLow",
    },
    {
        /*7*/
        .addr = MAX9860_REG_INTERFACE1,
        .name = "If1",
    },
    {
        /*8*/
        .addr = MAX9860_REG_INTERFACE2,
        .name = "If2",
    },
    {
        /*9*/
        .addr = MAX9860_REG_VOICE_FILTER,
        .name = "VoiceFilt",
    },
    {
        /*10*/
        .addr = MAX9860_REG_DAC_ATTENUATION,
        .name = "DacAtt",
    },
    {
        /*11*/
        .addr = MAX9860_REG_ADC_OUTPUT_LEVELS,
        .name = "AdcOutLev",
    },
    {
        /*12*/
        .addr = MAX9860_REG_DAC_GAIN_AND_SIDETONE,
        .name = "DacGainAndSide",
    },
    {
        /*13*/
        .addr = MAX9860_REG_MICROPHONE_GAIN,
        .name = "MicGain",
    },
    {
        /*14*/
        .addr = MAX9860_REG_RESERVED,
        .name = "Res",
    },
    {
        /*15*/
        .addr = MAX9860_REG_MICROPHONE_AGC,
        .name = "MicAGc",
    },
    {
        /*16*/
        .addr = MAX9860_REG_NOISE_GATEMICROPHONE_AGC,
        .name = "NoiseGateMicAgc",
    },
    {
        /*17*/
        .addr = MAX9860_REG_SYSTEM_SHUTDOWN,
        .name = "SusShut",
    },
    {
        /*18*/
        .addr = MAX9860_REG_REVISION_CODE,
        .name = "RegCode",
    },
};

uint32_t max9860_static_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(RegNameLUT);
    return cnt;
}

Max9860I2sRole_t max9860_bus_role_get(void) {
    Max9860I2sRole_t i2s_bus_role = MAX9860_I2SMODE_UNDEF;
    bool res = false;
    Max9860Reg06If1_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_INTERFACE1, &Reg.byte);
    if(res) {
        switch(Reg.mas) {
        case 1:
            i2s_bus_role = MAX9860_I2S_ROLE_MASTER;
            break;
        case 0:
            i2s_bus_role = MAX9860_I2S_ROLE_SLAVE;
            break;
        }
        LOG_DEBUG(MAX9860, "GetI2Srole %s", Max9860I2sRoleToStr(i2s_bus_role));
    }
    return i2s_bus_role;
}

static uint8_t Max9860I2sRole2Code(Max9860I2sRole_t i2s_role) {
    uint8_t mas = 0;
    LOG_DEBUG(MAX9860, "SetI2S_role %s", Max9860I2sRoleToStr(i2s_role));
    switch((uint8_t)i2s_role) {
    case MAX9860_I2S_ROLE_SLAVE:
        mas = 0;
        break;
    case MAX9860_I2S_ROLE_MASTER:
        mas = 1;
        break;
    }
    return mas;
}

bool max9860_save_mode_set(void) {
    bool res = false;
    res = max9860_dac_gain_set(DAC_GAIN_0);
    res = max9860_attenuation_set(0);
    return res;
}

/*Figure 11. Reading One Byte of Data from the MAX9860*/
bool max9860_reg_get(uint8_t addr, uint8_t* const reg_val) {
    bool res = false;
    LOG_DEBUG(MAX9860, "Read chip 0x%x Reg:0x%02x", MAX9860_7BIT_ADDRESS, addr);
#ifdef HAS_I2C
    // res = i2c_mcal_read_byte_v2(Max9860Config.i2c_num, MAX9860_7BIT_ADDRESS, addr, reg_val); // Zephyr Err
    res = i2c_mcal_read_byte(Max9860Config.i2c_num, MAX9860_7BIT_ADDRESS, addr, reg_val);
    if(res) {
        LOG_PARN(MAX9860, "ReadOk chip 0x%x Reg:0x%02x", MAX9860_7BIT_ADDRESS, addr);
    } else {
        LOG_ERROR(MAX9860, "Read chip 0x%x Reg:0x%02x", MAX9860_7BIT_ADDRESS, addr);
    }
#endif /*HAS_I2C*/
    return res;
}

bool max9860_reg_read_all(void) {
    bool res = false;
    uint8_t i = 0;
    uint8_t ok_cnt = 0;
    for(i = 0; i < MAX9860_REG_CNT; i++) {
        res = max9860_reg_get(Max9860RegVal[i].addr, &Max9860RegVal[i].value.byte);
        if(res) {
            ok_cnt++;
        } else {
            LOG_ERROR(I2C, "Read Reg:0x%02x Err", Max9860RegVal[i].addr);
        }
    }

    if(ok_cnt == MAX9860_REG_CNT) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#ifdef HAS_PARAM
bool max9860_load_params(Max9860RegVal_t* RegNode) {
    bool res = false;
    return res;
}
#endif

bool max9860_is_connected(void) {
    bool res = false;
    uint8_t reg_val = 0;
    res = max9860_reg_get(MAX9860_REG_REVISION_CODE, &reg_val);
    if(res) {
        if(MAX9860_REVISION_CODE == reg_val) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(MAX9860, "WrongRevCode 0x%02x Exp:0x%02x", reg_val, MAX9860_REVISION_CODE);
        }
    } else {
        LOG_ERROR(MAX9860, "ReadREgErr");
    }
    return res;
}

/*Figure 9. Writing One Byte of Data to the MAX9860*/
bool max9860_reg_set(uint8_t addr, uint8_t reg_val) {
    bool res = false;
    LOG_DEBUG(MAX9860, "Set Reg:0x%02x=%s Val:0x%02x", addr, Max9860RegAddr2Name(addr), reg_val);
#ifdef HAS_I2C
    res = i2c_api_reg_write(Max9860Config.i2c_num, MAX9860_7BIT_ADDRESS, addr, reg_val);
    if(false == res) {
        LOG_ERROR(MAX9860, "SetErr I2C:%u Chip:0x%x Data 0x%02x%02x", Max9860Config.i2c_num, MAX9860_7BIT_ADDRESS, addr,
                  reg_val);
    } else {
        LOG_DEBUG(MAX9860, "WrOk!");
    }
#endif /*HAS_I2C*/
    return res;
}

bool max9860_reg_set_verify(uint8_t addr, uint8_t set_reg_val) {
    bool res = false;
    cli_printf(CRLF);
    LOG_INFO(MAX9860, "SetVerify Reg:0x%02x Val:0x%02x", addr, set_reg_val);
    res = max9860_reg_set(addr, set_reg_val);
    if(res) {
        uint8_t reg_val_red = 0;
        res = max9860_reg_get(addr, &reg_val_red);
        if(reg_val_red == set_reg_val) {
            res = true;
            LOG_INFO(MAX9860, "SetVerify Reg:0x%02x Val:0x%02x Ok", addr, set_reg_val);
        } else {
            LOG_ERROR(MAX9860, "VerifyErr Reg:0x%02x Set:0x%02x != Get:0x%02x", addr, set_reg_val, reg_val_red);
            res = false;
        }
    }
    return res;
}

bool is_valid_gain(Gain_t gain) {
    bool res = false;
    if((-90 <= gain) && (gain <= 3)) {
        res = true;
    }
    return res;
}

bool max9860_reset(void) {
    bool res = false;
    Max9860Reg10SysShutdown_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_SYSTEM_SHUTDOWN, &Reg.byte);
    if(res) {
        Reg.shdn = 0;
        res = max9860_reg_set(MAX9860_REG_SYSTEM_SHUTDOWN, Reg.byte);
        wait_ms(20);

        Reg.shdn = 1;
        res = max9860_reg_set(MAX9860_REG_SYSTEM_SHUTDOWN, Reg.byte);
    }
    return res;
}

bool is_valid_voice_filter(DigitalFilter_t digital_filter) {
    bool res = false;
    if(digital_filter <= 5) {
        res = true;
    }
    return res;
}

bool max9860_voice_filter_set(Converter_t converter, DigitalFilter_t digital_filter) {
    bool res = false;

    res = is_valid_voice_filter(digital_filter);
    if(res) {
        Max9860Reg08DigitalFilter_t Reg;
        Reg.byte = 0;
        res = max9860_reg_get(MAX9860_REG_VOICE_FILTER, &Reg.byte);
        if(res) {
            switch(converter) {
            case CONV_ADC:
                Reg.avflt = digital_filter;
                break;
            case CONV_DAC:
                Reg.dvflt = digital_filter;
                break;
            default:
                break;
            }
            res = max9860_reg_set(MAX9860_REG_VOICE_FILTER, Reg.byte);
        }
    }
    return res;
}

DigitalFilter_t max9860_voice_filter_get(Converter_t converter) {
    bool res = false;
    DigitalFilter_t digital_filter = DIG_FILT_UNDEF;
    Max9860Reg08DigitalFilter_t Reg;
    Reg.byte = 0;
    res = max9860_reg_get(MAX9860_REG_VOICE_FILTER, &Reg.byte);
    if(res) {
        switch(converter) {
        case CONV_ADC:
            digital_filter = Reg.avflt;
            break;
        case CONV_DAC:
            digital_filter = Reg.dvflt;
            break;
        default:
            digital_filter = DIG_FILT_UNDEF;
            break;
        }
    }
    return digital_filter;
}

uint32_t max9860_reg_cnt(void) { return MAX9860_REG_CNT; }

/*Divides MCLK down to generate a PCLK between 10MHz and 20MHz.*/
uint8_t MclkHz2PsClk(uint32_t mclk_hz) {
    uint8_t code = PSCLK_DISABLE;
    if((10000000 < mclk_hz) && (mclk_hz < 20000000)) {
        code = PSCLK_MCLK_10MHZ_20MHZ;
    } else if((20000000 < mclk_hz) && (mclk_hz < 40000000)) {
        code = PSCLK_MCLK_20MHZ_40MHZ;
    } else if(40000000 < mclk_hz) {
        code = PSCLK_MCLK_40MHZ_PLUS;
    }
    return code;
}

uint32_t Mclk2Pclk(uint32_t mclk_hz) {
    uint32_t pclk_hz = mclk_hz;

    if((10000000 < mclk_hz) && (mclk_hz < 20000000)) {
        pclk_hz = mclk_hz;
    } else if((20000000 < mclk_hz) && (mclk_hz < 40000000)) {
        pclk_hz = ((double)mclk_hz) / 2.0;
    } else if(40000000 < mclk_hz) {
        pclk_hz = ((double)mclk_hz) / 4.0;
    } else {
        LOG_ERROR(MAX9860, "TooBig MCLK %u Hz", mclk_hz);
    }
    return pclk_hz;
}

uint8_t LrClkHzTo16kHzcode(uint32_t lrclk_hz) {
    uint8_t code = 0;
    switch(lrclk_hz) {
    case 8000:
        code = 0;
        break;
    case 16000:
        code = 1;
        break;
    default:
        code = 1;
        break;
    }
    return code;
}

uint8_t pclk12MHzToFreq(uint32_t lrclk_hz) {
    uint8_t freq = 0;
    switch(lrclk_hz) {
    case 8000:
    case 16000:
        freq = 1;
        break;
    default:
        freq = 0;
        break;
    }
    return freq;
}

uint8_t pclk13MHzToFreq(uint32_t lrclk_hz) {
    uint8_t freq = 0;
    switch(lrclk_hz) {
    case 8000:
    case 16000:
        freq = 2;
        break;
    default:
        freq = 0;
        break;
    }
    return freq;
}

uint8_t pclk19_2MHzToFreq(uint32_t lrclk_hz) {
    uint8_t freq = 0;
    switch(lrclk_hz) {
    case 8000:
    case 16000:
        freq = 3;
        break;
    default:
        freq = 0;
        break;
    }
    return freq;
}

uint8_t LrClkHzToFreqCode(uint32_t pclk_hz, uint32_t lrclk_hz) {
    uint8_t freq = 0;
    switch(pclk_hz) {
    case 12000000:
        freq = pclk12MHzToFreq(lrclk_hz);
        break;
    case 13000000:
        freq = pclk13MHzToFreq(lrclk_hz);
        break;
    case 19200000:
        freq = pclk19_2MHzToFreq(lrclk_hz);
        break;
    }
    return freq;
}

bool max9860_mclk_set(uint32_t mclk_hz, uint32_t lrclk_hz) {
    bool res = false;
    LOG_WARNING(MAX9860, "SetMclk: %u Hz", mclk_hz);

    Max9860Reg03SystemClock_t Reg;
    Reg.byte = 0;

    Reg.f16khz = LrClkHzTo16kHzcode(lrclk_hz);
    Reg.psclk = MclkHz2PsClk(mclk_hz);
    Reg.freq = LrClkHzToFreqCode(mclk_hz, lrclk_hz);

    res = max9860_reg_set(MAX9860_REG_SYSTEM_CLOCK, Reg.byte);

    return res;
}

/*See Table 4. Common N Values */
static uint16_t mclk_12mhz_get_n(uint32_t lrclk_hz) {
    uint16_t n_rec = 0;
    switch(lrclk_hz) {
    case 8000:
        n_rec = 0x1062;
        break;
    case 16000:
        n_rec = 0x20C5;
        break;
    case 32000:
        n_rec = 0x4189;
        break;
    case 44100:
        n_rec = 0x5A51;
        break;
    case 48000:
        n_rec = 0x624E;
        break;
    default:
        break;
    }
    return n_rec;
}

static uint16_t mclk_12_288_mhz_get_n(uint32_t lrclk_hz) {
    uint16_t n_rec = 0;
    switch(lrclk_hz) {
    case 8000:
        n_rec = 0x1000;
        break;
    case 16000:
        n_rec = 0x2000;
        break;
    case 32000:
        n_rec = 0x4000;
        break;
    case 44100:
        n_rec = 0x5833;
        break;
    case 48000:
        n_rec = 0x6000;
        break;
    default:
        break;
    }
    return n_rec;
}

static uint16_t mclk_xxxxx_mhz_get_n(uint32_t lrclk_hz) {
    uint16_t n_rec = 0;
    /*TODO*/
    LOG_ERROR(MAX9860, "ImplementLater");
    switch(lrclk_hz) {
    case 8000:
        n_rec = 0xFFFF;
        break;
    case 16000:
        n_rec = 0xFFFF;
        break;
    case 32000:
        n_rec = 0xFFFF;
        break;
    case 44100:
        n_rec = 0xFFFF;
        break;
    case 48000:
        n_rec = 0xFFFF;
        break;
    default:
        break;
    }
    return n_rec;
}

uint16_t max9860_recomended_n(const Max9860Config_t* const Config) {
    uint16_t n_rec = 0;
    switch(Config->mclk_hz) {
    case 11289600:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    case 12000000:
        n_rec = mclk_12mhz_get_n(Config->lrclk_hz);
        break;
    case 12288000:
        n_rec = mclk_12_288_mhz_get_n(Config->lrclk_hz);
        break;
    case 13000000:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    case 19200000:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    case 24000000:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    case 26000000:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    case 27000000:
        n_rec = mclk_xxxxx_mhz_get_n(Config->lrclk_hz);
        break;
    default:
        break;
    }
    return n_rec;
}

bool max9860_sample_rate_set(const Max9860Config_t* const Config) {
    bool res = false;
    LOG_WARNING(MAX9860, "SetSampleRate:%u Hz", Config->lrclk_hz);

    uint16_t rec_n = max9860_recomended_n(Config);
    if(0xFFFF != rec_n) {

        LOG_INFO(MAX9860, "Nrec:0x%04x=%u", rec_n, rec_n);

        // fPCLK = prescaled MCLK internal clock frequency (PCLK)
        uint32_t f_pclk_hz = Mclk2Pclk(Config->mclk_hz);
        LOG_INFO(MAX9860, "PCLK %u Hz", f_pclk_hz);
        double calc_n_d = (65536.0 * 96.0 * ((double)Config->lrclk_hz)) / ((double)f_pclk_hz);
        LOG_INFO(MAX9860, "Ncalc:%f", calc_n_d);
        uint16_t calc_n = (uint16_t)calc_n_d;
        LOG_INFO(MAX9860, "Ncalc:0x%04x=%u", calc_n, calc_n);

        if(calc_n != rec_n) {
            LOG_ERROR(MAX9860, "Nrec NotEqualTo Ncalc:0x%04x=0x%04x", rec_n, calc_n);
        }

        Max9860Reg04StereoAudioClockControlHight_t Reg4;
        Reg4.pll = 1;
        Reg4.nhi = WORD_HI_BYTE(rec_n);
        res = max9860_reg_set(MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_HIGH, Reg4.byte);

        Max9860Reg05StereoAudioClockControlLow_t Reg5;
        Reg5.nlo = WORD_LO_BYTE(rec_n);
        res = max9860_reg_set(MAX9860_REG_STEREO_AUDIO_CLOCK_CONTROL_LOW, Reg5.byte);
    }

    return res;
}

bool max9860_bus_role_set(Max9860I2sRole_t i2s_role) {
    bool res = false;
    LOG_DEBUG(MAX9860, "SetI2Srole %s", Max9860I2sRoleToStr(i2s_role));
    Max9860Reg06If1_t RefIf;
    RefIf.byte = 0;
    res = max9860_reg_get(MAX9860_REG_INTERFACE1, &RefIf.byte);
    if(res) {
        RefIf.mas = Max9860I2sRole2Code(i2s_role);
        res = max9860_reg_set(MAX9860_REG_INTERFACE1, RefIf.byte);
    }
    return res;
}

bool max9860_interface_set_i2s(const Max9860Config_t* const Config) {
    bool res = false;
    LOG_WARNING(MAX9860, "SetI2S");

    // 0x06
    // WCI=0 DBCI=0 DDLY=1
    Max9860Reg06If1_t RegIf1;
    RegIf1.byte = 0;
    // Read reg;
    RegIf1.wci = WCI_LEFT_CH_LRCLK_LOW;
    RegIf1.dbci = DBCI_SDOUT_VALID_ON_BCLK_RISING_EDGE;
    RegIf1.ddly = DDLY_2ND_BCLK;
#ifdef MAX9860_ADC
    RegIf1.hiz = HIZ_SDOUT_HI_IMPEDANCE;
#endif
    RegIf1.tdm = TDM_LRCLK_LEFT_AND_RIGHT;
    RegIf1.res = 0;
    RegIf1.mas = Max9860I2sRole2Code(Config->i2s_role);

    res = max9860_reg_set(MAX9860_REG_INTERFACE1, RegIf1.byte);

    Max9860Reg07If2_t RegIf2;
    RegIf2.byte = 0;

    RegIf2.bsel = BSEL_64X_LRCLK;
    RegIf2.st = ST_STEREO_ENABLE;
    RegIf2.adly = DDLY_2ND_BCLK;
    RegIf2.abci = DBCI_SDOUT_VALID_ON_BCLK_RISING_EDGE;
    RegIf2.res = 0;

    res = max9860_reg_set(MAX9860_REG_INTERFACE2, RegIf2.byte);

    return res;
}

bool max9860_interface_set_tdm(const Max9860Config_t* const Config) {
    bool res = false;
    LOG_WARNING(MAX9860, "SetTDM");
    return res;
}

bool max9860_interface_set(const Max9860Config_t* const Config) {
    bool res = false;
    LOG_WARNING(MAX9860, "SetIf %u", Config->interface);
    switch(Config->interface) {
    case MAX_IF_I2S:
        res = max9860_interface_set_i2s(Config);
        break;
    case MAX_IF_TDM:
        res = max9860_interface_set_tdm(Config);
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool max9860_init(void) {
    bool res = true;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint32_t err_cnt = 0;
    set_log_level(MAX9860, LOG_LEVEL_INFO);
    LOG_WARNING(MAX9860, "Init..");
#ifdef HAS_I2S
    set_log_level(I2S, LOG_LEVEL_DEBUG);
#endif

#ifdef HAS_I2C
    set_log_level(I2C, LOG_LEVEL_DEBUG);
#endif
    uint32_t cnt = max9860_get_config_cnt();
    LOG_INFO(MAX9860, "Spot %u CfgRegs", cnt);

    res = max9860_is_connected();
    // res = true;
    if(res) {

        Max9860RegVal_t Max9860RegConfig[MAX9860_REG_CNT];

        if(2 == sizeof(Max9860RegVal_t)) {
            memcpy((void*)Max9860RegConfig, (void*)Max9860RegValConfigLUT, cnt * sizeof(Max9860RegVal_t));
            for(i = 0; i < cnt; i++) {
                Max9860RegConfig[i] = Max9860RegValConfigLUT[i];
            }

#ifdef HAS_PARAM
            res = max9860_load_params(Max9860RegConfig);
#endif
            for(i = 0; i < cnt; i++) {
                uint32_t t = 0;
                for(t = 0; t < REG_SET_TRY_CNT; t++) {
                    wait_ms(200); // 200 works
                    res = max9860_reg_set_verify(Max9860RegConfig[i].addr, Max9860RegConfig[i].value.byte);
                    if(res) {
                        t = REG_SET_TRY_CNT * 2;
                        LOG_DEBUG(MAX9860, "SetOk!  0x%02x 0x%02x", Max9860RegConfig[i].addr,
                                  Max9860RegConfig[i].value.byte);
                        ok_cnt++;

                    } else {
                        LOG_ERROR(MAX9860, "SetErr 0x%02x 0x%02x try: %u", Max9860RegConfig[i].addr,
                                  Max9860RegConfig[i].value.byte, t);
                        err_cnt++;
                    }
                }
            }
            // res = max9860_volume_set(6);
        }

        res = max9860_bus_role_set(Max9860Config.i2s_role);
        res = max9860_dac_gain_set(Max9860Config.dac_gain);
        res = max9860_attenuation_set(Max9860Config.dac_attenuation);
        res = max9860_mclk_set(Max9860Config.mclk_hz, Max9860Config.lrclk_hz);
        res = max9860_sample_rate_set(&Max9860Config);
        res = max9860_interface_set(&Max9860Config);
        res = max9860_stereo_set(Max9860Config.stereo);
#ifdef HAS_MAX9860_VERIFY
        LOG_INFO(MAX9860, "VerifySound..");
        wait_ms(1000);
        res = max9860_attenuation_set(-20);
        res = max9860_play_1kHz_tone_limited((SampleType_t)MAX9860_VERIFY_AMP, 0, MAX9860_VERIFY_DURATION_MS);
#endif /**/
    } else {
        LOG_ERROR(MAX9860, "I2C%u LinkErr", Max9860Config.i2c_num);
    }

    if(ok_cnt == cnt) {
        LOG_INFO(MAX9860, "Config All %u Regs!", cnt);
    } else {
        LOG_ERROR(MAX9860, "Config %u/%u Regs %f %%", ok_cnt, cnt, FRACTION_TO_PERCENTAGE(ok_cnt, cnt));
    }
#ifdef HAS_I2C
    set_log_level(I2C, LOG_LEVEL_INFO);
#endif /**/

#ifdef HAS_I2S
    set_log_level(I2S, LOG_LEVEL_INFO);
#endif /**/
    set_log_level(MAX9860, LOG_LEVEL_INFO);
    return res;
}

bool max9860_proc_int_status(Max9860Reg00InterruptStatus_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->cld) {
            /*Indicates that a signal has become clipped in the ADC or DAC digital signal paths. CLD also
              indicates that the AGC function, when enabled, has set the microphone PGA to 0dB and no further gain
              reduction is possible.*/
            LOG_DEBUG(MAX9860, "ClipDetect");
        }
        if(Node->sld) {
            LOG_INFO(MAX9860, "SlewLevelDetect");
        }
        if(Node->ulk) {
            LOG_DEBUG(MAX9860, "DigitalPLLUnlock");
        }
    }
    return res;
}

bool max9860_proc(void) {
    bool res = false;
    LOG_DEBUG(MAX9860, "Proc");

    res = max9860_is_connected();
    if(res) {
        LOG_DEBUG(MAX9860, "I2C LinkOk");
        Max9860Reg00InterruptStatus_t RegStatus;
        RegStatus.byte = 0;
        res = max9860_reg_get(MAX9860_REG_INTERRUPT_STATUS, &RegStatus.byte);
        if(res) {
            res = max9860_proc_int_status(&RegStatus);
        }
    } else {
        LOG_ERROR(MAX9860, "I2C LinkLost");
    }
    return res;
}

/*Cove Utests*/
uint32_t max9860_pcm_2_32bit_sample(int32_t tx_sample) {
    uint32_t sample_data = 0;
    memcpy(&sample_data, &tx_sample, 4);
    sample_data = sample_data << 16;
    return sample_data;
}

const Max9860RegName_t* max9860RegAddr2Node(Max9860RegAddr_t addr) {
    const Max9860RegName_t* Node = NULL;
    uint32_t cnt = max9860_static_reg_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(addr == RegNameLUT[i].addr) {
            Node = &RegNameLUT[i];
            break;
        }
    }
    return Node;
}

bool max9860_is_valid_addr(uint8_t addr) {
    bool res = false;
    const Max9860RegName_t* Node = max9860RegAddr2Node(addr);
    if(Node) {
        res = true;
    }

    return res;
}
