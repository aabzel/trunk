#include "pll_calc.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "data_utils.h"
#include "log.h"
#include "sys_config.h"
#include "utils_math.h"

bool pll_calc_artery_f413(int32_t freq_xtal_hz, int32_t need_freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;
    LOG_INFO(PLL_CALC, "FreqXtal:%u Hz,FreqSys:%u  Hz", freq_xtal_hz, need_freq_sys_hz);
#ifdef HAS_CUSTOM_PRINTF
    cli_printf("{  (  {Xtal:%uHz} /pllhexdiv )*pllmult ]  = Sys:%u Hz" CRLF, freq_xtal_hz, need_freq_sys_hz);
#endif
    uint32_t solution_cnt = 0;
    if(PllArtety) {
        int32_t best_error_hz = INT_MAX;
        int32_t pllhexdiv = 0;
        int32_t cur_need_freq_sys_hz = 0;
        for(pllhexdiv = 1; pllhexdiv <= 2; pllhexdiv++) {
            int32_t pllmult = 0;
            for(pllmult = 2; pllmult <= 64; pllmult++) {
                cur_need_freq_sys_hz = ((pllmult * freq_xtal_hz) / (pllhexdiv));
                int32_t cur_error_hz = abs(cur_need_freq_sys_hz - need_freq_sys_hz);
                if(cur_error_hz < best_error_hz) {
                    best_error_hz = cur_error_hz;
                    solution_cnt++;
#ifdef HAS_CUSTOM_PRINTF
                    cli_printf("%u:Div:%1u,Mult:%2u,err:%d Hz,CPU:%u Hz" CRLF, solution_cnt, pllhexdiv, pllmult,
                               cur_error_hz, cur_need_freq_sys_hz);
#endif
                    PllArtety->pllhexdiv = pllhexdiv;
                    PllArtety->pllmult = pllmult;
                    PllArtety->core_freq_hz = cur_need_freq_sys_hz;
                    res = true;
                }
            }
        }
    }
    if(res) {
        LOG_INFO(PLL_CALC, "SpotPllVals!");
    } else {
        LOG_ERROR(PLL_CALC, "NoPllVals!");
    }
    return res;
}

bool pll_calc_artery_f43x(uint32_t freq_xtal_hz, uint32_t need_freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;

    LOG_INFO(PLL_CALC, "FreqXtal:%u Hz,FreqSys:%u  Hz", freq_xtal_hz, need_freq_sys_hz);
#ifdef HAS_CUSTOM_PRINTF
    cli_printf("{ [ (  {Xtal:%uHz} /M )*N ]/FR  }= Sys:%u Hz" CRLF, freq_xtal_hz, need_freq_sys_hz);
#endif
    uint32_t solution_cnt = 0;
    if(PllArtety) {
        uint32_t m = 0;
        uint32_t temp_hz = 0;
        uint32_t temp_m_hz = 0;
        uint32_t cur_need_freq_sys_hz = 0;
        for(m = 1; m <= 15; m++) {
            uint32_t n = 0;
            temp_m_hz = freq_xtal_hz / m;
            if(2000000 <= temp_m_hz) {
                if(temp_m_hz <= 16000000) {
                    for(n = 31; n <= 500; n++) {
                        uint32_t f = 0;
                        for(f = 0; f <= 5; f++) {
                            uint32_t fr = ipow(2, f);
                            cur_need_freq_sys_hz = ((n * freq_xtal_hz) / (m * fr));
                            if(need_freq_sys_hz == cur_need_freq_sys_hz) {
                                temp_hz = freq_xtal_hz * n / m; /*condition from Artery New Clock Config*/
                                if(500000000 <= temp_hz) {
                                    if(temp_hz <= 1200000000) {
                                        solution_cnt++;
#ifdef HAS_CUSTOM_PRINTF
                                        cli_printf("%u: MS:%2u,NS:%3u,FR:%2u" CRLF, solution_cnt, m, n, fr);
#endif
                                        PllArtety->ms = m;
                                        PllArtety->ns = n;
                                        PllArtety->fr = fr;
                                        res = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(res) {
        LOG_INFO(PLL_CALC, "SpotPllVals! %u Solutions", solution_cnt);
    } else {
        LOG_ERROR(PLL_CALC, "NoPllVals!");
    }
    return res;
}

bool pll_calc_artery(uint32_t freq_xtal_hz, uint32_t need_freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;
    res = pll_calc_artery_f43x(freq_xtal_hz, need_freq_sys_hz, PllArtety);

    res = pll_calc_artery_f413(freq_xtal_hz, need_freq_sys_hz, PllArtety);
    return res;
}

int32_t Fc7ClockSourceToValue(const Fc7ClockPllSource_t source) {
    uint32_t init_clock = 0;
    switch(source) {
    case FC73X_CLOCK_PLL_SOURCE_FOSC:
        init_clock = PLL_XTALL_FREQ_HZ;
        break;
    case FC73X_CLOCK_PLL_SOURCE_FIRC_DIV2:
        init_clock = FIRC_FREQ_HZ / 2;
        break;
    default:
        init_clock = 1;
        break;
    }
    return init_clock;
}

static bool pll_fc7300_is_pll_config(const PllFc7300Config_t* const Node) {
    bool res = false;
    int32_t mult = Node->mult + 1;
    int32_t in_clock_hz = (int32_t)Fc7ClockSourceToValue(Node->source);
    int32_t pre_div = (int32_t)(Node->pre_div + 1);
    int32_t feed_back = in_clock_hz / pre_div;
    int32_t post_div = (int32_t)Fc7ClockPostDivToValue(Node->post_div);

    if(96 < mult) {
        if(PLL_FEEDBACK_CLK_MIN <= feed_back) {
            if(feed_back <= PLL_FEEDBACK_CLK_MAX) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        int32_t vco_freq = feed_back * mult;
        if(PLL_VCO_CLK_MIN <= vco_freq) {
            if(vco_freq <= PLL_VCO_CLK_MAX) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        int32_t cur_freq_hz = ((in_clock_hz / pre_div) * mult) / (post_div);
        if(PLL_CLK_MIN <= cur_freq_hz) {
            if(cur_freq_hz <= PLL_CLK_MAX) {
                res = true;
            }
        }
    }
    return res;
}

int32_t pll_fc7300_calc(const PllFc7300Config_t* const Node) {
    int32_t in_clock_hz = (int32_t)Fc7ClockSourceToValue(Node->source);
    int32_t pre_div = (int32_t)(Node->pre_div + 1);
    int32_t mult = Node->mult + 1;
    int32_t divcore = Node->div_core + 1;
    int32_t post_div = (int32_t)Fc7ClockPostDivToValue(Node->post_div);
    int32_t cur_freq_hz = (((in_clock_hz / pre_div) * mult) / post_div) / divcore;
    return cur_freq_hz;
}

uint32_t Fc7ClockPostDivToValue(const Fc73xClockPostDiv_t post_div) {
    uint32_t post_div_real = 1;
    switch(post_div) {
    case FC7_CLOCK_POSR_DIV_2:
        post_div_real = 2;
        break;
    case FC7_CLOCK_POSR_DIV_2_:
        post_div_real = 2;
        break;
    case FC7_CLOCK_POSR_DIV_4:
        post_div_real = 4;
        break;
    case FC7_CLOCK_POSR_DIV_8:
        post_div_real = 8;
        break;
    default:
        post_div_real = 1;
        break;
    }
    return post_div_real;
}

static bool is_valid_pllq(const uint32_t pllq_out) {
    bool res = false;
    if(PLL_USB_CLOCK_HZ == pllq_out) {
        res = true;
    }
#if 0
    if(pllq_out <= 75000000) {
    }
#endif
    return res;
}

bool pll_stm32_is_valid_config(const PllStm32Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        uint32_t m = Config->M;
        uint32_t n = Config->N;
        uint32_t p = Config->P;
        uint32_t q = Config->Q;
        // uint32_t cur_sysclk = Config->core_freq_hz;
        uint32_t freq_xtal_hz = Config->xtall_freq_hz;

        uint32_t pllm_out = freq_xtal_hz / m;
        uint32_t plln_out = pllm_out * n;
        uint32_t pllq_out = plln_out / q; // USB clock
        uint32_t pllp_out = plln_out / p;
        if(res) {
            res = is_range_uint32(pllm_out, 950000, 2100000);
        }

        if(res) {
            res = is_valid_pllq(pllq_out);
        }

        if(res) {
            res = is_range_uint32(plln_out, 100000000, 432000000);
        }

        if(res) {
            res = is_range_uint32(pllp_out, 24000000, 168000000);
        }
    }
    return res;
}

const uint32_t p_vals[4] = {2, 4, 6, 8};
bool pll_calc_stm32_config(const uint32_t freq_xtal_hz, const uint32_t in_need_freq_sys_hz,
                           PllStm32Config_t* const Config) {
    bool res = false;

    PllStm32Config_t TempConfig = {0};
    TempConfig.core_freq_hz = in_need_freq_sys_hz;
    TempConfig.xtall_freq_hz = freq_xtal_hz;
    TempConfig.error_freq_hz = INT_MAX;
    Config->core_freq_hz = in_need_freq_sys_hz;
    Config->xtall_freq_hz = freq_xtal_hz;

    int32_t need_freq_sys_hz = (int32_t)in_need_freq_sys_hz;
    LOG_DEBUG(PLL_CALC, "FreqXtal:%u Hz,FreqSys:%u Hz", freq_xtal_hz, need_freq_sys_hz);
#ifdef HAS_CUSTOM_PRINTF
    LOG_DEBUG(PLL_CALC, "SolveEquation: [      ( {Xtal:%uHz} /M )*N    ]/P  = SysClk:%u Hz" CRLF, freq_xtal_hz,
              need_freq_sys_hz);
#endif

    if(freq_xtal_hz) {
        if(need_freq_sys_hz) {
            if(Config) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        int32_t min_abs_error_freq_hz = INT_MAX;
        uint32_t m = 0;
        for(m = 2; m <= 63; m++) {
            uint32_t n = 0;
            int32_t pllm_out = freq_xtal_hz / m;
            res = is_range_uint32(pllm_out, 950000, 2100000);
            if(res) {
                res = false;
                for(n = 50; n <= 432; n++) {
                    int32_t plln_out = pllm_out * n;
                    res = is_range_uint32(plln_out, 100000000, 432000000);
                    if(res) {
                        res = false;
                        uint32_t q = 0;
                        for(q = 2; q <= 15; q++) {
                            int32_t pllq_out = plln_out / q;
                            res = is_valid_pllq(pllq_out);
                            if(res) {
                                uint32_t p_i = 0;
                                for(p_i = 0; p_i < 4; p_i++) {
                                    int32_t pllp_out = plln_out / p_vals[p_i];
                                    res = is_range_uint32(pllp_out, 24000000, 168000000);
                                    if(res) {
                                        res = false;
                                        TempConfig.M = m;
                                        TempConfig.N = n;
                                        TempConfig.P = p_vals[p_i];
                                        TempConfig.Q = q;
                                        bool cfg_valid = pll_stm32_is_valid_config(&TempConfig);
                                        if(cfg_valid) {
                                            int32_t cur_error_freq_hz = (need_freq_sys_hz - pllp_out);
                                            int32_t cur_abs_error_freq_hz = abs(cur_error_freq_hz);
                                            TempConfig.error_freq_hz = cur_error_freq_hz;
                                            if(cur_abs_error_freq_hz < min_abs_error_freq_hz) {
                                                memcpy(Config, &TempConfig, sizeof(PllStm32Config_t));
#ifdef HAS_PLL_CALC_DIAG
                                                LOG_DEBUG(PLL_CALC, "ValidConfig,AbsErr:%d,%s", cur_abs_error_freq_hz,
                                                          PllStm32ConfigToStr(Config));
#endif
                                                min_abs_error_freq_hz = cur_abs_error_freq_hz;
                                                if(0 == cur_error_freq_hz) {
#ifdef HAS_PLL_CALC_DIAG
                                                    LOG_DEBUG(PLL_CALC, "SpotSolution!,%s",
                                                              PllStm32ConfigToStr(Config));
#endif
                                                    res = true;
                                                    return res;
                                                }
                                            }
                                        } // if(cfg_valid)
                                    }
                                } // for(p_i=0;p_i<4;p_i++)
                            }     // if(PLL_USB_CLOCK_HZ==usb_freq_hz)
                        }         // for(q=2;q<=4;q++)
                    }             // res = is_range_uint32(plln
                }                 // for(n=50;n<=432;n++)
            }
        } // for(m=2;m<=63;m++)
    }
    return res;
}

bool pll_calc_fc7300_config(const uint32_t in_freq_hz, const uint32_t set_freq_hz, PllFc7300Config_t* const Config) {
    bool res = false;
    LOG_INFO(PLL_CALC, "In(XTALL):%u Hz,Out(PLL):%u Hz", in_freq_hz, set_freq_hz);
    if(in_freq_hz) {
        if(set_freq_hz) {
            if(Config) {
                res = true;
            }
        }
    }

    if(res) {
        res = false;
        uint32_t iteration = 0;
        res = false;
        PllFc7300Config_t Best = {
            .error_hz = 0xFFFFFFFF,
        };
        PllFc7300Config_t Code = {0};
        for(Code.source = 0; Code.source < 2; Code.source++) {
            for(Code.pre_div = 0; Code.pre_div < 32; Code.pre_div++) {
                for(Code.mult = 0; Code.mult < 512; Code.mult++) {
                    for(Code.post_div = 0; Code.post_div < 4; Code.post_div++) {
                        for(Code.div_core = 0; Code.div_core < 4; Code.div_core++) {
                            res = pll_fc7300_is_pll_config(&Code);
                            if(res) {
                                int32_t cur_freq_hz = pll_fc7300_calc(&Code);
                                Code.error_hz = (uint32_t)abs(cur_freq_hz - ((int32_t)set_freq_hz));
                                if(Code.error_hz < Best.error_hz) {
                                    Best = Code;
                                    iteration++;
#ifdef HAS_PLL_CALC_DIAG
                                    LOG_DEBUG(PLL_CALC, "Iter:%u,%s", iteration, PllConfigToStr(&Best));
#endif
                                }
                            }
                        }
                    }
                }
            }
        }

        if(iteration) {
            *Config = Best;
#ifdef HAS_PLL_CALC_DIAG
            LOG_INFO(PLL_CALC, "Iter:%u,%s", iteration, PllConfigToStr(&Best));
#endif
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}
