#include "pll_calc_diag.h"

#include <stdio.h>
#include <string.h>

#include "diag_inc.h"
#include "pll_calc.h"

const char* PllArtetyToStr(const PllArtety_t* const PllArtety) {
    static char name[80] = {0};
    if(PllArtety) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sExternalFreq:%u Hz", name, PllArtety->xtall_freq_hz);
#ifdef HAS_AT32F413
        snprintf(name, sizeof(name), "%sDiv:%1u,", name, PllArtety->pllhexdiv);
        snprintf(name, sizeof(name), "%sMult:%2u,", name, PllArtety->pllmult);
#endif
#ifdef HAS_AT32F43X
        snprintf(name, sizeof(name), "%sM:%2u,", name, PllArtety->ms);
        snprintf(name, sizeof(name), "%sN:%2u,", name, PllArtety->ns);
        snprintf(name, sizeof(name), "%sFR:%2u", name, PllArtety->fr);
#endif
        snprintf(name, sizeof(name), "%sCoreFreq:%u Hz", name, PllArtety->core_freq_hz);
    }
    return name;
}

const char* PllConfigToStr(const PllFc7300Config_t* const Config) {
    if(Config) {
        int32_t pll_out = pll_fc7300_calc(Config);
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sIn:%u,", text, Fc7ClockSourceToValue(Config->source));
        snprintf(text, sizeof(text), "%sPreDiv:%u,", text, Config->pre_div + 1);
        snprintf(text, sizeof(text), "%sMult:%u,", text, Config->mult + 1);
        snprintf(text, sizeof(text), "%sPostDiv:%u,", text, Fc7ClockPostDivToValue(Config->post_div));
        snprintf(text, sizeof(text), "%sDivCore:%u,", text, Config->div_core + 1);
        snprintf(text, sizeof(text), "%sError:%u Hz,", text, Config->error_hz);
        snprintf(text, sizeof(text), "%sOut:%u Hz", text, pll_out);
    }
    return text;
}

const char* PllStm32ConfigToStr(const PllStm32Config_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sHSE:%6u Hz,", text, Config->xtall_freq_hz);
        snprintf(text, sizeof(text), "%sSYSCLK:%8u Hz:", text, Config->core_freq_hz);
        snprintf(text, sizeof(text), "%sM:%2u,", text, Config->M);
        snprintf(text, sizeof(text), "%sN:%3u,", text, Config->N);
        snprintf(text, sizeof(text), "%sP:%1u,", text, Config->P);
        snprintf(text, sizeof(text), "%sQ:%2u,", text, Config->Q);
        snprintf(text, sizeof(text), "%sError:%6d Hz,", text, Config->error_freq_hz);
    }
    return text;
}

bool pll_calc_stm_all(const uint32_t xtal_freq_hz, const uint32_t sys_freq_hz_step) {
    bool out_res = false;
    uint32_t sysclk = 0;
    PllStm32Config_t Config = {0};
    for(sysclk = 1000000; sysclk <= 168000000; sysclk += sys_freq_hz_step) {
        bool res = pll_calc_stm32_config(xtal_freq_hz, sysclk, &Config);
        if(res) {
            out_res = true;
            cli_printf("%s" CRLF, PllStm32ConfigToStr(&Config));
        }
    }
    return out_res;
}
