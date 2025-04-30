#include "pll_calc.h"

#include <limits.h>
#include <stdlib.h>

#include "log.h"
#include "utils_math.h"

#ifdef HAS_AT32F413
bool pll_calc_artery_f413(int32_t freq_xtal_hz, int32_t freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;
    LOG_INFO(PLL_CALC, "FreqXtal:%u Hz,FreqSys:%u  Hz", freq_xtal_hz, freq_sys_hz);
#ifdef HAS_CUSTOM_PRINTF
    cli_printf("{  (  {Xtal:%uHz} /pllhexdiv )*pllmult ]  = Sys:%u Hz" CRLF, freq_xtal_hz, freq_sys_hz);
#endif
    uint32_t solution_cnt = 0;
    if(PllArtety) {
        int32_t best_error_hz = INT_MAX;
        int32_t pllhexdiv = 0;
        int32_t cur_freq_sys_hz = 0;
        for(pllhexdiv = 1; pllhexdiv <= 2; pllhexdiv++) {
            int32_t pllmult = 0;
            for(pllmult = 2; pllmult <= 64; pllmult++) {
                cur_freq_sys_hz = ((pllmult * freq_xtal_hz) / (pllhexdiv));
                int32_t cur_error_hz = abs(cur_freq_sys_hz - freq_sys_hz);
                if(cur_error_hz < best_error_hz) {
                    best_error_hz = cur_error_hz;
                    solution_cnt++;
#ifdef HAS_CUSTOM_PRINTF
                    cli_printf("%u:Div:%1u,Mult:%2u,err:%d Hz,CPU:%u Hz" CRLF, solution_cnt, pllhexdiv, pllmult,
                               cur_error_hz, cur_freq_sys_hz);
#endif
                    PllArtety->pllhexdiv = pllhexdiv;
                    PllArtety->pllmult = pllmult;
                    PllArtety->core_freq_hz = cur_freq_sys_hz;
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
#endif

#ifdef HAS_AT32F43X
bool pll_calc_artery_f43x(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;

    LOG_INFO(PLL_CALC, "FreqXtal:%u Hz,FreqSys:%u  Hz", freq_xtal_hz, freq_sys_hz);
#ifdef HAS_CUSTOM_PRINTF
    cli_printf("{ [ (  {Xtal:%uHz} /M )*N ]/FR  }= Sys:%u Hz" CRLF, freq_xtal_hz, freq_sys_hz);
#endif
    uint32_t solution_cnt = 0;
    if(PllArtety) {
        uint32_t m = 0;
        uint32_t temp_hz = 0;
        uint32_t temp_m_hz = 0;
        uint32_t cur_freq_sys_hz = 0;
        for(m = 1; m <= 15; m++) {
            uint32_t n = 0;
            temp_m_hz = freq_xtal_hz / m;
            if(2000000 <= temp_m_hz) {
                if(temp_m_hz <= 16000000) {
                    for(n = 31; n <= 500; n++) {
                        uint32_t f = 0;
                        for(f = 0; f <= 5; f++) {
                            uint32_t fr = ipow(2, f);
                            cur_freq_sys_hz = ((n * freq_xtal_hz) / (m * fr));
                            if(freq_sys_hz == cur_freq_sys_hz) {
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
#endif

bool pll_calc_artery(uint32_t freq_xtal_hz, uint32_t freq_sys_hz, PllArtety_t* const PllArtety) {
    bool res = false;
#ifdef HAS_AT32F43X
    res = pll_calc_artery_f43x(freq_xtal_hz, freq_sys_hz, PllArtety);
#endif

#ifdef HAS_AT32F413X
    res = pll_calc_artery_f413(freq_xtal_hz, freq_sys_hz, PllArtety);
#endif
    return res;
}
