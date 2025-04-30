#include "pll_calc_commands.h"

#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "pll_calc.h"
#include "pll_calc_diag.h"
/*
 * plaf43x 8000000 100000000
 * plaf43x 8000000 288000000
 * plaf43x 8000000 8000000
 * plaf43x 8000000 10000000 no
 * plaf43x 8000000 20000000
 * plaf43x 8000000 5000000
 * */
bool pll_calc_artery_f43x_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_AT32F43X
    uint32_t freq_xtal_hz = 8000000;
    uint32_t freq_sys_hz = 100000000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &freq_xtal_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &freq_sys_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[1]);
        }
    }

    if(res) {
        PllArtety_t PllArtety = {0};
        res = pll_calc_artery_f43x(freq_xtal_hz, freq_sys_hz, &PllArtety);
        if(res) {
            LOG_INFO(PLL_CALC, "%s", PllArtetyToStr(&PllArtety));
        } else {
            LOG_ERROR(PLL_CALC, "NoValues");
        }
    } else {
        LOG_ERROR(PLL_CALC, "Usage: plaf43x XtalFreqHz SysFreqHz");
    }
#endif
    return res;
}
bool pll_calc_artery_f413_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_AT32F413
    uint32_t freq_xtal_hz = 16000000;
    uint32_t freq_sys_hz = 100000000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &freq_xtal_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &freq_sys_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[1]);
        }
    }

    if(res) {
        PllArtety_t PllArtety = {0};
        res = pll_calc_artery_f413(freq_xtal_hz, freq_sys_hz, &PllArtety);
        if(res) {
            LOG_INFO(PLL_CALC, "%s", PllArtetyToStr(&PllArtety));
        } else {
            LOG_ERROR(PLL_CALC, "NoValues");
        }
    } else {
        LOG_ERROR(PLL_CALC, "Usage: plaf413 XtalFreqHz SysFreqHz");
    }
#endif
    return res;
}

bool pll_calc_stm_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}
