#include "nau8814_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "interfaces_diag.h"
#include "log.h"
#include "num_to_str.h"

#ifdef HAS_NAU8814_ADC
#include "nau8814_adc_diag.h"
#endif /**/

#ifdef HAS_NAU8814_DAC
#include "nau8814_dac_diag.h"
#endif /**/

#include "nau8814_drv.h"
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

const char* Nau8814ConfigToStr(const Nau8814Config_t* const Config) {
    static char name[80] = "";
    if(Config) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Config->i2c_num);
        snprintf(name, sizeof(name), "%sI2S:%u,", name, Config->i2s_num);
        snprintf(name, sizeof(name), "%sAddr:0x%x", name, Config->chip_addr);
    }
    return name;
}

const char* Nau8814PllInfoToStr(const Nau8814PllInfo_t* const PllInfo) {
    static char name[200] = "";
    if(PllInfo) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sMCLK:%sHz,", name, uint32ToStr(PllInfo->mclk_hz));
        snprintf(name, sizeof(name), "%sNeedFS:%sHz,", name, uint32ToStr(PllInfo->fs_hz));
        snprintf(name, sizeof(name), "%sD:%u,", name, PllInfo->D);
        snprintf(name, sizeof(name), "%sN:%u,", name, PllInfo->N);
        snprintf(name, sizeof(name), "%sK:%u,", name, PllInfo->K);
        snprintf(name, sizeof(name), "%sR:%s,", name, FloatToStr(PllInfo->R));
        snprintf(name, sizeof(name), "%sF1:%sHz,", name, FloatToStr(PllInfo->f_1));
        snprintf(name, sizeof(name), "%sF2:%sHz,", name, FloatToStr(PllInfo->f_2));
        snprintf(name, sizeof(name), "%sFpll:%sHz,", name, FloatToStr(PllInfo->f_pll));
        snprintf(name, sizeof(name), "%sIMCLK:%sHz,", name, FloatToStr(PllInfo->i_mclk));
        snprintf(name, sizeof(name), "%sRealFS:%6.1f Hz,", name, PllInfo->i_mclk / 256.0);
        float fs_err_hz = fabsf(PllInfo->i_mclk / 256.0 - ((float)PllInfo->fs_hz));
        snprintf(name, sizeof(name), "%sErrFS:%6.1f Hz,", name, fs_err_hz);
    }
    return name;
}

const char* Nau8814NodeToStr(const Nau8814Handle_t* const Node) {
    static char name[150] = "";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
        snprintf(name, sizeof(name), "%sI2C:%u,", name, Node->i2c_num);
        snprintf(name, sizeof(name), "%sI2S:%u,", name, Node->i2s_num);
        snprintf(name, sizeof(name), "%sAddr:0x%x,", name, Node->chip_addr);
        snprintf(name, sizeof(name), "%sPmicGain:%d,", name, Node->p_mic_gain);
        snprintf(name, sizeof(name), "%sAdcOn:%u,", name, Node->adc_on);
        snprintf(name, sizeof(name), "%sDacGain:%d,", name, Node->dac_gain);
        snprintf(name, sizeof(name), "%sI2Srole:%s", name, BusRoleToStr(Node->i2s_role));
    }
    return name;
}

bool nau8814_diag_low_level(uint8_t num, const char* const key_word) {
    bool res = false;
    return res;
}

static const char* ValU16ToStar(uint16_t word) {
    const char* name = "";
    if(0 < word) {
        name = "*";
    }
    return name;
}

bool nau8814_reg_hazy(uint8_t num) {
    bool res = false;
    LOG_INFO(NAU8814, "HazyRegs");
    static const table_col_t cols[] = {
        {5, "No"}, {6, "addrD"}, {6, "addrH"}, {8, "val"}, {21, "val [bin]"}, {6, "mark"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    uint32_t cnt = 0;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = nau8814_is_valid_addr(some_addr);
        if(false == res) {
            uint16_t word = 0;
            res = nau8814_reg_read(num, some_addr, &word);
            if(res) {
                if(word) {
                    strcpy(text, TSEP);
                    snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                    snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                    snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin16(word));
                    snprintf(text, sizeof(text), "%s %4s " TSEP, text, ValU16ToStar(word));
                    cli_printf(TSEP " %3u ", cnt);
                    cli_printf("%s" CRLF, text);
                    wait_in_loop_ms(10);
                    cnt++;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(0 < cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool nau8814_reg_map_diag(uint8_t num, char* key_word, char* key_word2) {
    bool res = false;
    uint32_t addr = 0;
    uint32_t cnt = 0;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "addrD"}, {6, "addrH"}, {8, "val"}, {21, "val [bin]"}, {21, "name"},
    };
    char text[120] = "";
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(addr = 0; addr < 0xFF; addr++) {
        const Nau8814RegInfo_t* Info = Nau8814RegAddrToInfo(addr);
        if(Info) {
            uint16_t word = 0;
            res = nau8814_reg_read(num, addr, &word);
            if(res) {
                strcpy(text, TSEP);
                cli_printf(TSEP " %3u ", cnt);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, addr);
                snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin16(word));
                snprintf(text, sizeof(text), "%s %19s " TSEP, text, Info->name);
                cli_printf("%s" CRLF, text);
                wait_in_loop_ms(10);
                cnt++;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    if(0 < cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool nau8814_reg_map_hidden_diag(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "addr"}, {6, "addr"}, {8, "val"}, {11, "val [bin]"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char text[120] = "";
    int32_t i = 0;
    int32_t cnt = 0;
    for(i = 0; i <= 127; i++) {
        uint8_t some_addr = i;
        res = nau8814_is_valid_addr(some_addr);
        if(false == res) {
            uint16_t word = 0;
            res = nau8814_reg_read(num, some_addr, &word);
            if(res) {
                strcpy(text, TSEP);
                snprintf(text, sizeof(text), "%s %4u " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%02x " TSEP, text, some_addr);
                snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, word);
                snprintf(text, sizeof(text), "%s %9s " TSEP, text, utoa_bin16(word));
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, text);
                cnt++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

// Table 25: Registers associated with PLL
bool nau8814_diag_pll(uint8_t num) {
    bool res = false;
    LOG_INFO(NAU8814, "DiagPll");

    const Nau8814Config_t* Config = Nau8814GetConfig(num);
    if(Config) {
        double f_1 = 1.0;
        double f_2 = 1.0;
        double imclk = 1.0;
        uint8_t N = 0;
        uint8_t D = 0;
        uint32_t K = 0;
        res = nau8814_pll_d_get(num, &D);
        res = nau8814_pll_n_get(num, &N);
        res = nau8814_pll_k_get(num, &K);
        f_1 = Config->mclk_freq_hz / ((double)D);
        double fractional = ((double)K) / ((double)TWO_POW_24);
        double R = ((double)N) + fractional;
        // R = f_2/f_1;
        f_2 = R * f_1;
        double f_pll = f_2 / 4.0;
        double P = 1.0;
        res = nau8814_master_clock_div_get(num, &P);
        imclk = f_pll / ((double)P);

        char text[300] = "";
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sMCLK:%sHz,", text, DoubleToStr(Config->mclk_freq_hz));
        snprintf(text, sizeof(text), "%sD:%u,", text, D);
        snprintf(text, sizeof(text), "%sN:%u,", text, N);
        snprintf(text, sizeof(text), "%sK:%u,", text, K);
        snprintf(text, sizeof(text), "%sR:%f,", text, R);
        snprintf(text, sizeof(text), "%sP:%2.1f,", text, P);
        snprintf(text, sizeof(text), "%sF1:%sHz,", text, DoubleToStr(f_1));
        snprintf(text, sizeof(text), "%sF2:%sHz,", text, DoubleToStr(f_2));
        snprintf(text, sizeof(text), "%sFpll:%sHz,", text, DoubleToStr(f_pll));
        snprintf(text, sizeof(text), "%sIMCLK:%sHz,", text, DoubleToStr(imclk));
        LOG_INFO(NAU8814, "%s", text);

        res = true;
    }
    return res;
}

bool nau8814_diag_high_level(uint8_t num) {
    bool res = false;
    LOG_INFO(NAU8814, "DiagHighLevel");

    res = nau8814_is_connected(num);
    if(res) {
        LOG_INFO(NAU8814, "Connected %s", OnOffToStr(res));
        Nau8814Handle_t* Node = Nau8814GetNode(num);
        if(Node) {
            res = nau8814_i2s_role_get(num, &Node->i2s_role);
            LOG_INFO(NAU8814, " %s", Nau8814NodeToStr(Node));
        }
        res = nau8814_diag_pll(num) && res;
    }

    return res;
}

const char* Nau8814RegAddrToName(Nau8814RegAddr_t addr) {
    const char* name = "?";
    const Nau8814RegInfo_t* Info = Nau8814RegAddrToInfo(addr);
    if(Info) {
        name = Info->name;
    }
    return name;
}
