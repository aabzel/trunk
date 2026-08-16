#include "pll_calc_commands.h"


#include "convert.h"
#include "log.h"
#include "num_to_str.h"
#include "pll_calc.h"
#include "pll_calc_diag.h"

#ifdef HAS_CAN
#include "can_mcal.h"
#include "can_segments_stm32.h"
#endif
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
    uint32_t xtal_freq_hz = 8000000;
    uint32_t sys_freq_hz = 100000000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &xtal_freq_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &sys_freq_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[1]);
        }
    }

    if(res) {
        PllArtety_t PllArtety = {0};
        res = pll_calc_artery_f43x(xtal_freq_hz, sys_freq_hz, &PllArtety);
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
    uint32_t xtal_freq_hz = 16000000;
    uint32_t sys_freq_hz = 100000000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &xtal_freq_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &sys_freq_hz);
        if(false == res) {
            LOG_ERROR(PLL_CALC, "ParseErr [%s]", argv[1]);
        }
    }

    if(res) {
        PllArtety_t PllArtety = {0};
        res = pll_calc_artery_f413(xtal_freq_hz, sys_freq_hz, &PllArtety);
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
#ifdef HAS_CAN
    uint32_t xtal_freq_hz = 8000000;
    uint32_t sys_freq_hz = 100000000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &sys_freq_hz);
        log_info_res(PLL_CALC, res, "GetCoreFreq");
        LOG_INFO(PLL_CALC, "sys_freq %u Hz", sys_freq_hz);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &xtal_freq_hz);
        log_info_res(PLL_CALC, res, "GetXtalFreq");
    }

    if(res) {
        PllStm32Config_t Config = {0};
        res = pll_calc_stm32_config(xtal_freq_hz, sys_freq_hz, &Config);
        if(res) {
            LOG_WARNING(PLL_CALC, "OK,%s", PllStm32ConfigToStr(&Config));
        } else {
            LOG_ERROR(PLL_CALC, "NoSolution,TheNearestSolutionIs,%s", PllStm32ConfigToStr(&Config));
        }
    } else {
        LOG_ERROR(PLL_CALC, "Usage: pls SysFreqHz XtalFreqHz");
    }
#endif

    return res;
}

/*
 pll_calc_stm32_all 25000000 1000000
 */
bool pll_calc_stm_all_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t xtal_freq_hz = 8000000;
    uint32_t sys_freq_hz_step = 500000;

    if(0 <= argc) {
        res = true;
        xtal_freq_hz = 8000000;
        sys_freq_hz_step = 500000;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &xtal_freq_hz);
        log_info_res(PLL_CALC, res, "GetXtallFreq");
        LOG_INFO(PLL_CALC, "FOSC_FREQUENCY:%u Hz", xtal_freq_hz);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &sys_freq_hz_step);
        log_info_res(PLL_CALC, res, "GetStepFreq");
        LOG_INFO(PLL_CALC, "sys_freq_hz_step:%u Hz", sys_freq_hz_step);
    }

    if(res) {
        res = pll_calc_stm_all(xtal_freq_hz, sys_freq_hz_step);
        log_info_res(PLL_CALC, res, "StmAll");
    } else {
        LOG_ERROR(PLL_CALC, "Usage: plsta xtal_freq_hz stepHz");
    }

    return res;
}

bool pll_calc_fc7300_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t xtal_freq_hz = 16000000;
    uint32_t sys_freq_hz = 300000000;
    LOG_INFO(PLL_CALC, "FIRC_CLOCK %u Hz", FIRC_CLOCK);
    LOG_INFO(PLL_CALC, "%u<PLL_VCO_CLK<%u Hz", PLL_VCO_CLK_MIN, PLL_VCO_CLK_MAX);
    LOG_INFO(PLL_CALC, "%u<PLL_CLK<%u Hz", PLL_CLK_MIN, PLL_CLK_MAX);

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &sys_freq_hz);
        log_info_res(PLL_CALC, res, "GetCoreFreq");
        LOG_INFO(PLL_CALC, "sys_freq %u Hz", sys_freq_hz);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &xtal_freq_hz);
        log_info_res(PLL_CALC, res, "GetXtalFreq");
    }

    if(res) {
        PllFc7300Config_t Config = {0};
        res = pll_calc_fc7300_config(xtal_freq_hz, sys_freq_hz, &Config);
        if(res) {
            LOG_INFO(PLL_CALC, "OK,%s", PllConfigToStr(&Config));
        } else {
            LOG_ERROR(PLL_CALC, "NoSolution");
        }
    } else {
        LOG_ERROR(PLL_CALC, "Usage: plfc SysFreqHz XtalFreqHz");
    }
    return res;
}

/*
 scsc 24000000 100000
 */
bool stm32_can_segment_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_CAN
    uint32_t bus_freq_hz = 24000000;
    uint32_t bit_rate_hz = 100000;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &bus_freq_hz);
        log_info_res(CAN, res, "bus_freq_hz");
        LOG_INFO(CAN, "sys_freq %u Hz", bus_freq_hz);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &bit_rate_hz);
        log_info_res(CAN, res, "bit_rate_hz");
        LOG_INFO(CAN, "bit_rate:%u Hz", bit_rate_hz);
    }

    if(res) {
        CanSegmentInfo_t Segment = {0};
        switch(argc) {
        case 1: {
            res = bxcan_segment_info_calc_all(bus_freq_hz);
        } break;
        case 2: {
            res = bxcan_segment_info_calc(bus_freq_hz, bit_rate_hz, &Segment);
            LOG_INFO(CAN, "OK,%s", CanSegmentInfoToStr(&Segment));
        } break;
        default: {

        } break;
        }

        if(res) {
        } else {
            LOG_ERROR(CAN, "NoSolution");
        }
    } else {
        LOG_ERROR(CAN, "Usage: scsc bus_freq_hz bit_rate_hz");
    }
#endif
    return res;
}
