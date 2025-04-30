#include "clock_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_custom.h"
#include "clock_diag.h"
#include "common_diag.h"
#include "log.h"
#include "nrfx_clock.h"
#include "table_utils.h"
#include "writer_config.h"

static const char* ClcDivider2Str(nrf_clock_hfclk_div_t divider) {
    const char* name = "?";
    switch(divider) {
    case NRF_CLOCK_HFCLK_DIV_1:
        name = "1/1";
        break;
    case NRF_CLOCK_HFCLK_DIV_2:
        name = "1/2";
        break;
    case NRF_CLOCK_HFCLK_DIV_4:
        name = "1/4";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static const char* NrfClkLFreq2Str(nrf_clock_lfclk_t lfclk) {
    const char* name = "?";
    switch(lfclk) {
    case NRF_CLOCK_LFCLK_LFULP:
        name = "Int32kHzUlpOsc";
        break; /**< Internal 32 kHz Ultra-low power oscillator. */
    case NRF_CLOCK_LFCLK_RC:
        name = "Int32kHzRcOsc";
        break; /**< Internal 32 kHz RC oscillator. */
    case NRF_CLOCK_LFCLK_Xtal:
        name = "Ext32kHzXtal";
        break; /**< External 32 kHz crystal. */
    // case NRF_CLOCK_LFCLK_Synth   :name = "Int32kHzSynFromHfclkSysClk"; break;  /**< Internal 32 kHz synthesizer from
    // HFCLK system clock. */ case NRF_CLOCK_LFCLK_Xtal_Low_Swing   : name = "Xtal_Low_Swing";break; case
    // NRF_CLOCK_LFCLK_Xtal_Full_Swing   : name = "Xtal_Full_Swing";break;
    default:
        name = "?";
        break;
    }
    return name;
}

static const char* NrfClkHiFreq2Str(nrf_clock_hfclk_t hfclk) {
    const char* name = "?";
    switch(hfclk) {
    case NRF_CLOCK_HFCLK_LOW_ACCURACY:
        name = "Int16MHz";
        break; /**< Internal 16 MHz RC oscillator. */
    case NRF_CLOCK_HFCLK_HIGH_ACCURACY:
        name = "Ext32MHz";
        break; /**< External 32 MHz crystal oscillator. */
    default:
        name = "?";
        break;
    }
    return name;
}

bool clock_diag_low_level(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 4;
    char line[150];
    static const table_col_t cols[] = {
        {8, "DomNum"}, {8, "DomNRF"}, {12, "DomStr"}, {10, "FreqHz"},   {5, "Src"},
        {5, "Div"},    {4, "En"},     {8, "ClkSrc"},  {16, "LFreqSrc"}, {10, "HiFreqSrc"},
    };
    bool is_running = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    NrfxClkSrc_t NrfxClkSrc;
    for(i = 0; i < cnt; i++) {
        NrfxClkSrc.byte = 0;
        uint32_t freq_hz = clock_freq_get(ClockInfo[i].domain_nrf);
        ClockSource_t src = clock_nrf_src_get(ClockInfo[i].domain_nrf);

        is_running = nrfx_clock_is_running(ClockInfo[i].domain_nrf, (void*)&NrfxClkSrc.byte);

        nrf_clock_hfclk_div_t div = nrfx_clock_divider_get((nrf_clock_domain_t)ClockInfo[i].domain_nrf);
        strcpy(line, TSEP);
        snprintf(line, sizeof(line), "%s %6u " TSEP, line, ClockInfo[i].domain_num);
        snprintf(line, sizeof(line), "%s %6u " TSEP, line, ClockInfo[i].domain_nrf);
        snprintf(line, sizeof(line), "%s %10s " TSEP, line, ClockInfo[i].name);
        snprintf(line, sizeof(line), "%s %8u " TSEP, line, freq_hz);
        snprintf(line, sizeof(line), "%s %3s " TSEP, line, ClkSrc2Str(src));
        snprintf(line, sizeof(line), "%s %3s " TSEP, line, ClcDivider2Str(div));
        snprintf(line, sizeof(line), "%s %2u " TSEP, line, is_running);
        snprintf(line, sizeof(line), "%s %6u " TSEP, line, NrfxClkSrc.byte);
        snprintf(line, sizeof(line), "%s %14s " TSEP, line, NrfClkLFreq2Str(NrfxClkSrc.byte));
        snprintf(line, sizeof(line), "%s %8s " TSEP, line, NrfClkHiFreq2Str(NrfxClkSrc.byte));
        cli_printf("%s" CRLF, line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool clock_diag_low_freq(void) {
    bool res = true;
    nrf_clock_lfclk_t clock_lfclk;
    bool is_running = nrfx_clock_is_running(NRF_CLOCK_DOMAIN_LFCLK, (void*)&clock_lfclk);
    LOG_INFO(CLK, "IsRun: %u ", is_running);
    LOG_INFO(CLK, "ClockSrc %s ", NrfClkLFreq2Str(clock_lfclk));

    clock_lfclk = nrf_clock_lf_src_get(NRF_CLOCK_S);
    LOG_INFO(CLK, "LowFreqSrc: %u=%s", clock_lfclk, NrfClkLFreq2Str(clock_lfclk));

    clock_lfclk = nrf_clock_lf_actv_src_get(NRF_CLOCK_S);
    LOG_INFO(CLK, "LowFreqActivSrc:%u=%s", clock_lfclk, NrfClkLFreq2Str(clock_lfclk));

    return res;
}

bool clock_diag_high_frequency(void) {
    bool res = true;
    char line[150];
    strcpy(line, "");
    nrf_clock_hfclk_t hf_clk_src = 0;

    res = nrfx_clock_is_running(NRF_CLOCK_DOMAIN_HFCLK, NULL);
    snprintf(line, sizeof(line), "%s HFCLK:%s, ", line, OnOff2Str(res));

    hf_clk_src = nrf_clock_hf_src_get(NRF_CLOCK_S);
    snprintf(line, sizeof(line), "%s HfClkSrc:%u=%s, ", line, hf_clk_src, NrfClkHiFreq2Str(hf_clk_src));

    hf_clk_src = nrf_clock_hfclk192m_src_get(NRF_CLOCK_S);
    snprintf(line, sizeof(line), "%s ExHfClkSrc:%u=%s, ", line, hf_clk_src, NrfClkHiFreq2Str(hf_clk_src));

    bool run = nrf_clock_alwaysrun_get(NRF_CLOCK_S, NRF_CLOCK_DOMAIN_HFCLK);
    snprintf(line, sizeof(line), "%s RunHFClk:%u, " TSEP, line, run);

    run = nrf_clock_alwaysrun_get(NRF_CLOCK_S, NRF_CLOCK_DOMAIN_HFCLK192M);
    snprintf(line, sizeof(line), "%s RunHFClk192M:%u, ", line, run);

    nrf_clock_hfclk_div_t divider = 0;
    divider = nrf_clock_hfclk_div_get(NRF_CLOCK_S);
    snprintf(line, sizeof(line), "%s HfClkDiv:%u=%s, ", line, divider, ClcDivider2Str(divider));

    divider = nrf_clock_hfclk192m_div_get(NRF_CLOCK_S);
    snprintf(line, sizeof(line), "%s ExHfClkDiv:%u=%s", line, divider, ClcDivider2Str(divider));

    LOG_INFO(CLK, "%s", line);
    return res;
}
