#include "clock_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_custom_types.h"
#include "log.h"
#include "module_driver_csc.h"
#include "table_utils.h"
#include "writer_config.h"

/*
  SCG - System Clock Generator
 */
static const ClockSCGSourceInfo_t ClockSCGSourceInfo[] = {
    {
        .clk_src_type = SCG_CORE_CLK,
        .name = "CORE",
        .valid = true,
    },
    {
        .clk_src_type = SCG_BUS_CLK,
        .name = "BUS",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SLOW_CLK,
        .name = "SLOW",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FOSC_CLK,
        .name = "FOSC",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FIRC_CLK,
        .name = "FIRC",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL0_CLK,
        .name = "PLL0",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL1_CLK,
        .name = "PLL1",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SIRC_CLK,
        .name = "SIRC",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SIRC32K_CLK,
        .name = "SIRC32K",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SOSC_CLK,
        .name = "SOSC",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SCG_CLKOUT_CLK,
        .name = "SCG_CLKOUT",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SIRCDIVH_CLK,
        .name = "SIRCDIVH",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SIRCDIVM_CLK,
        .name = "SIRCDIVM",
        .valid = true,
    },
    {
        .clk_src_type = SCG_SIRCDIVL_CLK,
        .name = "SIRCDIVL",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FIRCDIVH_CLK,
        .name = "FIRCDIVH",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FIRCDIVM_CLK,
        .name = "FIRCDIVM",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FIRCDIVL_CLK,
        .name = "FIRCDIVL",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FOSCDIVH_CLK,
        .name = "FOSCDIVH",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FOSCDIVM_CLK,
        .name = "FOSCDIVM",
        .valid = true,
    },
    {
        .clk_src_type = SCG_FOSCDIVL_CLK,
        .name = "FOSCDIVL",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL0DIVH_CLK,
        .name = "PLL0DIVH",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL0DIVM_CLK,
        .name = "PLL0DIVM",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL0DIVL_CLK,
        .name = "PLL0DIVL",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL1DIVH_CLK,
        .name = "PLL1DIVH",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL1DIVM_CLK,
        .name = "PLL1DIVM",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL1DIVL_CLK,
        .name = "PLL1DIVL",
        .valid = true,
    },
    {
        .clk_src_type = SCG_NVMINIT_CLK,
        .name = "NVMINIT",
        .valid = true,
    },
    {
        .clk_src_type = SCG_CMU4REF_CLK,
        .name = "CMU4REF",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL0CLK1,
        .name = "PLL0CLK1",
        .valid = true,
    },
    {
        .clk_src_type = SCG_PLL1CLK1,
        .name = "PLL1CLK1",
        .valid = true,
    },
    {
        .clk_src_type = SCG_END_OF_CLOCKS,
        .name = "END_OF_CLOCKS",
        .valid = true,
    },
};

bool clock2_diag(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ClockSCGSourceInfo);
    char line[150];
    static const table_col_t cols[] = {
        {5, "Src"},
        {15, "Name"},
        {12, "FreqHz"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(i = 0; i < cnt; i++) {
        uint32_t freq_hz = 0;
        freq_hz = SCG_GetScgClockFreq(ClockSCGSourceInfo[i].clk_src_type);
        strcpy(line, TSEP);
        snprintf(line, sizeof(line), "%s %3u " TSEP, line, ClockSCGSourceInfo[i].clk_src_type);
        snprintf(line, sizeof(line), "%s %13s " TSEP, line, ClockSCGSourceInfo[i].name);
        snprintf(line, sizeof(line), "%s %10u " TSEP, line, freq_hz);
        cli_printf("%s" CRLF, line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

static const ClockSourceInfo_t ClockSourceInfo[] = {
    {
        .clk_src_type = CSC0_AON32K_CLK,
        .name = "AON32K",
        .valid = true,
    },
    {
        .clk_src_type = CSC0_RTC_CLK,
        .name = "RTC",
        .valid = true,
    },
    {
        .clk_src_type = CSC0_AON_CLK,
        .name = "AON",
        .valid = true,
    },
    {
        .clk_src_type = CSC0_CLKOUT_CLK,
        .name = "CLKOUT",
        .valid = true,
    },
    {
        .clk_src_type = CSC0_END_OF_CLOCKS,
        .name = "END_OF",
        .valid = true,
    },
};

bool clock1_diag(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ClockSourceInfo);
    char line[150];
    static const table_col_t cols[] = {
        {5, "Src"},
        {15, "Name"},
        {5, "stat"},
        {12, "FreqHz"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(i = 0; i < cnt; i++) {
        uint32_t freq_hz = 0;
        // SCG_GetScgClockFreq
        CSC_RetStatusType ret = CSC0_GetCSC0ClockFreq(ClockSourceInfo[i].clk_src_type, &freq_hz);
        strcpy(line, TSEP);
        snprintf(line, sizeof(line), "%s %3u " TSEP, line, ClockSourceInfo[i].clk_src_type);
        snprintf(line, sizeof(line), "%s %13s " TSEP, line, ClockSourceInfo[i].name);
        snprintf(line, sizeof(line), "%s %3u " TSEP, line, ret);
        snprintf(line, sizeof(line), "%s %10u " TSEP, line, freq_hz);
        cli_printf("%s" CRLF, line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
