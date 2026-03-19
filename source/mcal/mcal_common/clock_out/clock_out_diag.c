#include "clock_out_diag.h"

#include "clock_out_types.h"

const char* ClockOutBusToStr(const ClockOutBus_t freq) {
    const char* name = "?";
    switch(freq) {
    case CLOCK_OUT_CORE:
        name = "CORE";
        break;
    case CLOCK_OUT_PLL0:
        name = "PLL0";
        break;
    case CLOCK_OUT_PLL1:
        name = "PLL1";
        break;
    case CLOCK_OUT_RTC:
        name = "RTC";
        break;
    case CLOCK_OUT_AON:
        name = "AON";
        break;
    case CLOCK_OUT_SIRC_128K:
        name = "128K";
        break;
    case CLOCK_OUT_BUS:
        name = "BUS";
        break;
    case CLOCK_OUT_FIRC:
        name = "FIRC";
        break;
    case CLOCK_OUT_SIRC:
        name = "SIRC";
        break;
    case CLOCK_OUT_SLOW:
        name = "SLOW";
        break;
    case CLOCK_OUT_FOSC:
        name = "FOSC";
        break;
    case CLOCK_OUT_SCG:
        name = "SCG";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}
