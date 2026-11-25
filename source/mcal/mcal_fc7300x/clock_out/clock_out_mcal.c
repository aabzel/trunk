#include "clock_out_mcal.h"

#include "HwA_csc.h"
#include "log.h"
#include "module_driver_csc.h"

static bool ClockOutRetToRes(CSC_RetStatusType ret) {
    bool res = false;
    switch(ret) {
    case CSC_E_OK:
        res = true;
        break;
    case CSC_E_NOT_OK:
        res = false;
        break;
    default:
        break;
    }
    return res;
}

static bool ClockOutRetToEclkOutSrc(const ClockOutBus_t bus_clock) {
    CSC0_ClockOutSrcType out_src = CSC0_CLKOUT_SCG_CLKOUT;
    switch(bus_clock) {
    case CLOCK_OUT_RTC:
        out_src = CSC0_CLKOUT_RTC_CLK;
        break;
    case CLOCK_OUT_AON:
        out_src = CSC0_CLKOUT_AON_CLK;
        break;
    case CLOCK_OUT_SIRC_128K:
        out_src = CSC0_CLKOUT_SIRC_128K_CLK;
        break;
    case CLOCK_OUT_BUS:
        out_src = CSC0_CLKOUT_BUS_CLK;
        break;
    case CLOCK_OUT_PLL0:
        out_src = CSC0_CLKOUT_PLL0_DIVM_CLK;
        break;
    case CLOCK_OUT_CORE:
        out_src = CSC0_CLKOUT_CORE_CLK;
        break;
    case CLOCK_OUT_FIRC:
        out_src = CSC0_CLKOUT_FIRC_DIVM_CLK;
        break;
    case CLOCK_OUT_PLL1:
        out_src = CSC0_CLKOUT_PLL1_DIVM_CLK;
        break;
    case CLOCK_OUT_SIRC:
        out_src = CSC0_CLKOUT_SIRC_DIVM_CLK;
        break;
    case CLOCK_OUT_SLOW:
        out_src = CSC0_CLKOUT_SLOW_CLK;
        break;
    case CLOCK_OUT_FOSC:
        out_src = CSC0_CLKOUT_FOSC_DIVM_CLK;
        break;
    case CLOCK_OUT_SCG:
        out_src = CSC0_CLKOUT_SCG_CLKOUT;
        break;
    default:
        break;
    }
    return out_src;
}

static CSC0_ClockOutDivType ClockOutDivToEdivider(const uint32_t divider) {
    CSC0_ClockOutDivType out_div = CSC0_CLKOUT_DIV_BY8;
    out_div = (divider - 1);
    return out_div;
}

bool clock_out_set(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t divider) {
    bool res = true;
    LOG_WARNING(CLK, "Set,CLOCK_OUT_%u,FreqSrc:%s,Div:%u", ch, ClockOutBusToStr(clock_bus), divider);
    CSC0_ClkoutType Csc0ClkOut = {0};
    Csc0ClkOut.bEnable = true;
    Csc0ClkOut.eClkOutSrc = ClockOutRetToEclkOutSrc(clock_bus);
    Csc0ClkOut.eDivider = ClockOutDivToEdivider(divider);

    CSC_RetStatusType ret = CSC_E_NOT_OK;
    ret = CSC0_SetClockOut(&Csc0ClkOut, false);
    res = ClockOutRetToRes(ret);
    return res;
}

bool clock_out_get(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t* freq_hz) {
    bool res = true;
    CSC0_ClkSrcType clk_name = ClockOutRetToEclkOutSrc(clock_bus);

    CSC_RetStatusType ret = CSC_E_NOT_OK;
    ret = CSC0_GetCSC0ClockFreq(clk_name, freq_hz);
    res = ClockOutRetToRes(ret);
    LOG_DEBUG(CLK, "Get,CLOCK_OUT_%u,FreqSrc:%s,Freq:%u Hz", ch, ClockOutBusToStr(clock_bus), *freq_hz);
    return res;
}

bool clock_out_init_one(uint8_t num) {
    bool res = false;
    const ClockOutConfig_t* Config = ClockOutGetConfig(num);
    if(Config) {
        res = clock_out_set(Config->channel, Config->clock_bus, Config->divider);
    }
    return res;
}
