#include "fda801_commands.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "fda801_config.h"
#include "fda801_diag.h"
#include "fda801_drv.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "test_fda801.h"
#include "writer_config.h"

static bool fda801_read_reg_map(char* key_word1, char* key_word2) {
    bool res = false;
    LOG_INFO(FDA801, "key1:[%s] key2:[%s]", key_word1, key_word2);
    static const table_col_t cols[] = {{5, "No"},  {6, "Addr"},    {11, "BinAddr"},
                                       {6, "Val"}, {11, "BinVal"}, {20, "name"}};
    uint16_t num = 1;
    uint16_t reg_cnt = 0;
    reg_cnt = fda801_reg_cnt();
    LOG_INFO(FDA801, "RegCnt:%u", reg_cnt);
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char line_str[120];
    for(i = 0; i < reg_cnt; i++) {
        strncpy(line_str, TSEP, sizeof(line_str));
        snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, Fda801RegMap[i].reg_addr);
        snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str, utoa_bin8(Fda801RegMap[i].reg_addr));
        uint8_t reg_val = 0;
        res = fda801_read_reg(Fda801RegMap[i].reg_addr, &reg_val);
        snprintf(line_str, sizeof(line_str), "%s 0x%02x " TSEP, line_str, reg_val);
        snprintf(line_str, sizeof(line_str), "%s %9s " TSEP, line_str, utoa_bin8(reg_val));
        snprintf(line_str, sizeof(line_str), "%s %18s " TSEP, line_str, Fda801RegMap[i].name);
        if(is_contain(line_str, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s", line_str);
            cli_printf(CRLF);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool fda801_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(GPIO, "Usage: gl keyWord");
    }
    if(res) {
        res = fda801_read_reg_map(keyWord1, keyWord2);
    } else {
        LOG_ERROR(FDA801, "Usage: fdam");
    }
    return res;
}

bool fda801_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr RegAddr %s", argv[0]);
        }
    }
    if(res) {
        res = fda801_read_reg(reg_addr, &reg_val);
        if(false == res) {
            LOG_ERROR(FDA801, "ReadErr [0x%02x]", reg_addr);
        } else {
            LOG_INFO(FDA801, "ReadOk [0x%02x]=0x%02x", reg_addr, reg_val);
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fdar RegAddr");
    }
    return res;
}

bool fda801_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t reg_addr = 0;
    uint8_t reg_val = 0;
    char bit_mask[11] = "****_****";
    if(2 == argc) {
        res = try_str2uint8(argv[0], &reg_addr);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr RegAddr %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &reg_val);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr RegVal %s", argv[1]);
            strcpy(bit_mask, argv[1]);
            res = is_valid_bit_mask_u8(bit_mask);
        }
    }
    if(res) {
        res = is_valid_bit_mask_u8(bit_mask);
        if(res) {
            LOG_INFO(FDA801, "StopBitMask [%s]", bit_mask);
            res = fda801_write_reg_by_bitmask(reg_addr, bit_mask);
        } else {
            res = fda801_write_reg(reg_addr, reg_val);
            if(false == res) {
                LOG_ERROR(FDA801, "WriteErr [0x%02x]=0x%02x", reg_addr, reg_val);
            } else {
                LOG_INFO(FDA801, "WriteOk [0x%02x]=0x%02x", reg_addr, reg_val);
            }
        }
    } else {
        LOG_ERROR(FDA801, "Usage1: fdaw RegAddr RegVal");
        LOG_ERROR(FDA801, "Usage2: fdaw RegAddr BitMask");
    }
    return res;
}

bool fda801_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = fda801_reset();
    } else {
        LOG_ERROR(FDA801, "Usage: fdat");
    }
    return res;
}

#define FDA801_PARSE_REG(REG_NAME, PARSER_NAME)                                                                        \
    do {                                                                                                               \
        uint8_t reg8_val = 0;                                                                                          \
        bool res = false;                                                                                              \
        LOG_INFO(FDA801, "ReadReg 0x%x", REG_NAME);                                                                    \
        res = fda801_read_reg(REG_NAME, &reg8_val);                                                                    \
        if(res) {                                                                                                      \
            LOG_INFO(FDA801, "ReadRegOk 0x%x Val:0x%x", REG_NAME, reg8_val);                                           \
            res = PARSER_NAME(reg8_val, keyWord1);                                                                     \
        } else {                                                                                                       \
            LOG_ERROR(FDA801, "ReadRegErr 0x%x", REG_NAME);                                                            \
            out_res = false;                                                                                           \
        }                                                                                                              \
    } while(0);

bool fda801_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        Fda801Handle_t* Fda801Node = Fda801GetNode(FDA801_MAIN);
        if(Fda801Node) {
            LOG_INFO(FDA801, "RegWrDisaccord: %u", Fda801Node->reg_val_disaccord);
            LOG_INFO(FDA801, "SpinCnt: %u", Fda801Node->spin_cnt);
            res = true;
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fdadl");
    }
    return res;
}

bool fda801_diag_command(int32_t argc, char* argv[]) {
    bool out_res = true;
    bool res = false;
    char keyWord1[20] = "";
    if(0 == argc) {
        res = true;
    }
    if(1 == argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(res) {
        uint8_t i2c_addr = fda801_get_chip_addr(FDA801_MAIN);
        LOG_INFO(FDA801, "ChipAddr: 0x%02x", i2c_addr);
        if(i2c_addr) {
            out_res = true;
        } else {
            out_res = false;
        }
        FDA801_PARSE_REG(REG_INTERFACE, fda801_parse_if);
        FDA801_PARSE_REG(REG_CR1, fda801_parse_cr1);
        FDA801_PARSE_REG(REG_CR2, fda801_parse_cr2);
        FDA801_PARSE_REG(REG_DIAG, fda801_parse_diag);
        FDA801_PARSE_REG(REG_DIAGSEL, fda801_parse_diagsel);
        FDA801_PARSE_REG(REG_CHN1CNTR, fda801_parse_ch1_ctrl);
        FDA801_PARSE_REG(REG_CHN2CNTR, fda801_parse_ch2_ctrl);
        FDA801_PARSE_REG(REG_CHN3CNTR, fda801_parse_ch3_ctrl);
        FDA801_PARSE_REG(REG_CHN4CNTR, fda801_parse_ch4_ctrl);
        FDA801_PARSE_REG(REG_DIAGPHASEDELAYCNTRCH1, fda801_parse_ch1_diag_phase_sel_ctrl);
        FDA801_PARSE_REG(REG_DIAGPHASEDELAYCNTRCH2, fda801_parse_ch2_diag_phase_sel_ctrl);
        FDA801_PARSE_REG(REG_DIAGPHASEDELAYCNTRCH3, fda801_parse_ch3_diag_phase_sel_ctrl);
        FDA801_PARSE_REG(REG_DIAGPHASEDELAYCNTRCH4, fda801_parse_ch4_diag_phase_sel_ctrl);
        FDA801_PARSE_REG(REG_CHN1DCOUT, fda801_parse_ch1_dc_out);
        FDA801_PARSE_REG(REG_CHN2DCOUT, fda801_parse_ch2_dc_out);
        FDA801_PARSE_REG(REG_CHN3DCOUT, fda801_parse_ch3_dc_out);
        FDA801_PARSE_REG(REG_CHN4DCOUT, fda801_parse_ch4_dc_out);
        FDA801_PARSE_REG(REG_DIGITAL, fda801_parse_digital2);
        FDA801_PARSE_REG(REG_LCFILTERSETUP, fda801_parse_lc_filt_set);
        FDA801_PARSE_REG(REG_SENSOR, fda801_parse_sensor);
        FDA801_PARSE_REG(REG_THERMALWARNING, fda801_parse_termal);
        FDA801_PARSE_REG(REG_CH1CH2ACDIAGRES, fda801_parse_ch1ch2_ac_diag);
        FDA801_PARSE_REG(REG_CH3CH4ACDIAGRES, fda801_parse_ch3ch4_ac_diag);

    } else {
        LOG_ERROR(FDA801, "Usage: fdad keyWord");
    }
    return out_res;
}

bool fda801_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = fda801_init();
        if(false == res) {
            LOG_ERROR(FDA801, "Init" LOG_ER);
        } else {
            LOG_INFO(FDA801, "Init" LOG_OK);
        }
    }
    return res;
}

bool fda801_diag_channels(char* keyWord1) {
    bool res = false;
    uint8_t ch_num = 0;
    static const table_col_t cols[] = {
        {5, "No"},        {5, "Chan"},     {6, "State"},    {7, "DcDiagDatValid"}, {8, "loadOpen"},
        {8, "loadShort"}, {7, "shortGnd"}, {7, "shortVcc"}, {10, "OverCurr"},      {6, "Op"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char line_str[120];
    const Fda801Handle_t* Node = Fda801GetNode(FDA801_MAIN);
    for(ch_num = 0; ch_num < FDA801_CHANNEL_COUNT; ch_num++) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s %1u   " TSEP, line_str, ch_num + 1);
        snprintf(line_str, sizeof(line_str), "%s %s " TSEP, line_str,
                 ChannelStateToStr(Node->Channel[ch_num].DcOutput.state));
        snprintf(line_str, sizeof(line_str), "%s %5s " TSEP, line_str,
                 DcDiagDataValidToStr(Node->Channel[ch_num].DcOutput.dc_diag_dat_valid));
        snprintf(line_str, sizeof(line_str), "%s %6s " TSEP, line_str,
                 LoadOpenToStr(Node->Channel[ch_num].DcOutput.load_open));
        snprintf(line_str, sizeof(line_str), "%s %6s " TSEP, line_str,
                 ShortLoadToStr(Node->Channel[ch_num].DcOutput.load_short));
        snprintf(line_str, sizeof(line_str), "%s %5s " TSEP, line_str,
                 ShortGndToStr(Node->Channel[ch_num].DcOutput.short_gnd));
        snprintf(line_str, sizeof(line_str), "%s %5s " TSEP, line_str,
                 ShortVccToStr(Node->Channel[ch_num].DcOutput.short_vcc));
        snprintf(line_str, sizeof(line_str), "%s %8s " TSEP, line_str,
                 OverCurrentToStr(Node->Channel[ch_num].DcOutput.over_current));
        snprintf(line_str, sizeof(line_str), "%s %16s " TSEP, line_str,
                 DcOperationToStr(Node->Channel[ch_num].DcOutput.operation));

        if(is_contain(line_str, keyWord1, "")) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s", line_str);
            cli_printf(CRLF);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool fda801_channels(char* keyWord1) {
    bool res = false;
    uint8_t ch_num = 0;
    static const table_col_t cols[] = {{5, "No"},     {5, "chan"},   {6, "state"}, {5, "gain"},     {12, "Diag"},
                                       {6, "acDiag"}, {6, "dcDiag"}, {5, "Pwm"},   {6, "AcExtFlag"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char line_str[120];
    const Fda801Handle_t* Node = Fda801GetNode(FDA801_MAIN);
    for(ch_num = 0; ch_num < FDA801_CHANNEL_COUNT; ch_num++) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s %1u   " TSEP, line_str, ch_num + 1);
        snprintf(line_str, sizeof(line_str), "%s %4s " TSEP, line_str,
                 ChannelStateToStr(Node->Channel[ch_num].Reg.state));
        snprintf(line_str, sizeof(line_str), "%s %3s " TSEP, line_str, GainSelToStr(Node->Channel[ch_num].Reg.gain_sel));
        snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str, ChanDiagToStr(Node->Channel[ch_num].Reg.diag));
        snprintf(line_str, sizeof(line_str), "%s %4s " TSEP, line_str, OnOffToStr(Node->Channel[ch_num].Reg.ac_diag));
        snprintf(line_str, sizeof(line_str), "%s %4s " TSEP, line_str, OnOffToStr(Node->Channel[ch_num].Reg.dc_diag));
        snprintf(line_str, sizeof(line_str), "%s %3s " TSEP, line_str, OnOffToStr(Node->Channel[ch_num].Reg.pwm_on));
        snprintf(line_str, sizeof(line_str), "%s %3s " TSEP, line_str,
                 OnOffToStr(Node->Channel[ch_num].Reg.ac_ext_test_flag));

        if(is_contain(line_str, keyWord1, "")) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s", line_str);
            cli_printf(CRLF);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool fda801_set_channel_command(int32_t argc, char* argv[]) {
    bool res = false;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    Fda801ChannelState_t State = CH_STATE_UNDEF;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], (uint8_t*)&State);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr State %s", argv[1]);
        }
    }

    if(2 == argc && res) {
        res = fda801_set_state(Channel, State);
        if(res) {
            LOG_INFO(FDA801, "SetOk Ch%u %s", Channel, ChannelStateToStr(State));
        }
    }

    if(1 == argc && res) {
        State = fda801_get_state(Channel);
        if(res) {
            LOG_INFO(FDA801, "GetOk Ch%u %s", Channel, ChannelStateToStr(State));
        }
    }

    if(false == res) {
    }

    return res;
}

bool fda801_diag_channels_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    if(0 == argc) {
        res = true;
    }
    if(1 == argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(res) {
        res = fda801_diag_channels(keyWord1);
    } else {
        LOG_ERROR(FDA801, "Usage: fdadc keyWord");
    }
    return res;
}

bool fda801_channels_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    if(0 == argc) {
        res = true;
    }
    if(1 == argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(res) {
        res = fda801_channels(keyWord1);
    } else {
        LOG_ERROR(FDA801, "Usage: fdac keyWord");
    }
    return res;
}

bool fda801_channel_dc_diag_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
    }
    if(res) {
        res = fda801_channel_dc_diag_start(Channel);
        if(res) {
            LOG_INFO(FDA801, "DcDiagOk Channel %u", Channel);
        } else {
            LOG_ERROR(FDA801, "DcDiagErr Channel %u", Channel);
        }
    } else {
        LOG_ERROR(FDA801, "Usage fdacd Ch");
    }
    return res;
}

bool fda801_ac_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t ch_num = 0;
    static const table_col_t cols[] = {
        {5, "chan"},     {8, "Oper"}, //
        {5, "valid"},                 //
        {12, "Tweeter"}, {6, "warning"},

    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char line_str[120];
    const Fda801Handle_t* Node = Fda801GetNode(FDA801_MAIN);
    for(ch_num = 0; ch_num < FDA801_CHANNEL_COUNT; ch_num++) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s %1u   " TSEP, line_str, ch_num + 1);

        snprintf(line_str, sizeof(line_str), "%s %4s " TSEP, line_str,
                 AcOperationToStr(Node->Channel[ch_num].AcDiag.operation));
        snprintf(line_str, sizeof(line_str), "%s %3s " TSEP, line_str,
                 AcDiagDataValidToStr(Node->Channel[ch_num].AcDiag.valid));
        snprintf(line_str, sizeof(line_str), "%s %10s " TSEP, line_str,
                 AcDiagTweetToStr(Node->Channel[ch_num].AcDiag.tweeter));
        snprintf(line_str, sizeof(line_str), "%s %4s " TSEP, line_str,
                 AcDiagWarnToStr(Node->Channel[ch_num].AcDiag.warning));

        cli_printf("%s", line_str);
        cli_printf(CRLF);

        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool fda801_set_channel_pwm_command(int32_t argc, char* argv[]) {
    bool res = false;
    Fda801ChannelPwm_t pwm_state = CH_PWM_UNDEF;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], (uint8_t*)&pwm_state);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr PwmState %s", argv[1]);
        }
    }

    if(res) {
        if(2 == argc) {
            res = fda801_set_channel_pwm(Channel, pwm_state);
            if(res) {
                LOG_INFO(FDA801, "SetChanPwmOk Ch%u %s", Channel, ChPwmToStr(pwm_state));
            } else {
                LOG_ERROR(FDA801, "SetChanPwmErr Ch%u %s", Channel, ChPwmToStr(pwm_state));
            }
        } else if(1 == argc) {
            pwm_state = fda801_get_channel_pwm(Channel);
            LOG_INFO(FDA801, "GetChanPwmErr Ch%u %s", Channel, ChPwmToStr(pwm_state));
        } else {
            res = false;
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fdascp ch on");
    }
    return res;
}

bool fda801_channel_play_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = true;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr OnOff %s", argv[1]);
        }
    }

    if(res) {
        res = fda801_set_channel_play(Channel, on_off);
        if(res) {
            LOG_INFO(FDA801, "Ch %u PlayOk", Channel);
        } else {
            LOG_ERROR(FDA801, "ChPlayErr");
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fdcp Chan OnOff");
    }
    return res;
}

bool fda801_set_channel_gain_command(int32_t argc, char* argv[]) {
    bool res = false;
    Fda801ChannelGain_t Gain = GAIN_SEL_UNDEF;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    if(2 == argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
        res = try_str2uint8(argv[1], (uint8_t*)&Gain);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Gain %s", argv[1]);
        }
    }
    if(res) {
        res = fda801_set_channel_gain(Channel, Gain);
        if(res) {
            LOG_INFO(FDA801, "SetGainOk %s %u", ChannelToStr(Channel), Gain);
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fscg Chan Gain");
    }
    return res;
}

bool fda801_get_channel_gain_command(int32_t argc, char* argv[]) {
    bool res = false;
    Fda801ChannelGain_t Gain = GAIN_SEL_UNDEF;
    Fda801ChannelNum_t Channel = FDA_CHANNEL_UNDEF;
    if(1 == argc) {
        res = try_str2uint8(argv[0], (uint8_t*)&Channel);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr Channel %s", argv[0]);
        }
    }
    if(res) {
        res = fda801_get_channel_gain(Channel, &Gain);
        if(res) {
            LOG_INFO(FDA801, "GetGainOk %s %u", ChannelToStr(Channel), Gain);
        } else {
            LOG_ERROR(FDA801, "GetGainErr %s %u", ChannelToStr(Channel), Gain);
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fgcg Chan");
    }
    return res;
}

bool fda801_set_clock_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off;
    if(1 == argc) {
        res = try_str2bool(argv[0], &on_off);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr OnOff %s", argv[0]);
        }
    }

    if(res) {
        res = fda801_clock(on_off);
        if(res) {
            LOG_INFO(FDA801, "Clock %s", OnOffToStr(on_off));
        } else {
            LOG_ERROR(FDA801, "Clock %s", OnOffToStr(on_off));
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fsc OnOff");
    }
    return res;
}

bool fda801_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    double freq = 0.0;
    int32_t amplitude_32b = 0;
    if(1 <= argc) {
        res = try_str2double(argv[0], &freq);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr freq %s", argv[0]);
        }
    }
    if(2 <= argc) {
        res = try_str2int32(argv[1], &amplitude_32b);
        if(false == res) {
            LOG_ERROR(FDA801, "ParseErr amplitude %s", argv[1]);
        }
    }
    if(res) {
        res = test_fda801_play_freq(freq, (SampleType_t)amplitude_32b);
        if(res) {
            LOG_INFO(FDA801, "PlayOk");
        } else {
            LOG_ERROR(FDA801, "PlayErr");
        }
    } else {
        LOG_ERROR(FDA801, "Usage: fdt freq Amp");
    }
    return res;
}
