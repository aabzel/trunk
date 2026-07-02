#include "clock_out_mcal.h"

#include "log.h"
#include "clock_out_custom.h"
#include "clock_out_diag.h"
#include "clock_out_custom_diag.h"
#include "stm32fx_hal.h"

uint32_t McoNum2McoHal(McoChannel_t chan) {
    uint32_t rcc_mco = 0;
    switch((uint8_t)chan) {
    case MCO_1:        rcc_mco = RCC_MCO1;        break;
    case MCO_2:        rcc_mco = RCC_MCO2;        break;
    default:        break;
    }
    return rcc_mco;
}

static FrequencySource_t bus_clk_to_freq_src(const ClockOutBus_t bus_clock) {
    FrequencySource_t freq_src = FREQ_SRC_UNDEF;
    switch (bus_clock) {
        case CLOCK_OUT_RTC:  freq_src = FREQ_SRC_LSE;        break;
        case CLOCK_OUT_FOSC: freq_src = FREQ_SRC_HSE;        break;
        case CLOCK_OUT_FIRC: freq_src = FREQ_SRC_HSI;        break;
        case CLOCK_OUT_PLL0: freq_src = FREQ_SRC_PLL;        break;
        case CLOCK_OUT_PLL1: freq_src = FREQ_SRC_PLL;        break;


        case CLOCK_OUT_SIRC:
        case CLOCK_OUT_SLOW:
        case CLOCK_OUT_SCG:
        case CLOCK_OUT_BUS:
        case CLOCK_OUT_SIRC_128K:
        case CLOCK_OUT_AON:
        case CLOCK_OUT_CORE:
            freq_src = FREQ_SRC_UNDEF;
            break;
        default:
            freq_src = FREQ_SRC_UNDEF;
            break;
    }
    return freq_src;
}

uint32_t FreqCode2FreqHal(FrequencySource_t freq) {
    uint32_t code = 0;
    switch((uint8_t)freq) {
    case FREQ_SRC_LSE:
        code = RCC_MCO1SOURCE_LSE;
        break;
    case FREQ_SRC_HSE:
        code = RCC_MCO1SOURCE_HSE;
        break;
    case FREQ_SRC_HSI:
        code = RCC_MCO1SOURCE_HSI;
        break;
    case FREQ_SRC_PLL:
        code = RCC_MCO1SOURCE_PLLCLK;
        break;
    default:        break;
    }
    return code;
}

uint32_t Div2McoDiv(uint8_t divider) {
    uint32_t code = 0;
    switch((uint8_t)divider) {
    case 1:
        code = RCC_MCODIV_1;
        break;
    case 2:
        code = RCC_MCODIV_2;
        break;
    case 3:
        code = RCC_MCODIV_3;
        break;
    case 4:
        code = RCC_MCODIV_4;
        break;
    case 5:
        code = RCC_MCODIV_5;
        break;
    default:        break;
    }
    return code;
}

bool mco_config(McoChannel_t ch, FrequencySource_t freq, uint8_t divider) {
    bool res = true;
    LOG_WARNING(CLK, "Config MCO_%u FreqSrc:%s Div:%u", ch, Freq2Str(freq), divider);

    uint32_t rcc_mco = McoNum2McoHal(ch);
    uint32_t rcc_mco_src = FreqCode2FreqHal(freq);
    uint32_t rcc_mco_div = Div2McoDiv(divider);
    HAL_RCC_MCOConfig(rcc_mco, rcc_mco_src, rcc_mco_div);
    return res;
}

bool clock_out_set(ClockOutChannel_t ch, ClockOutBus_t bus_clock, uint32_t divider){
    FrequencySource_t freq_src = bus_clk_to_freq_src(bus_clock);
    bool res = mco_config( (McoChannel_t )ch, freq_src, (uint8_t) divider);
    return res;
}

bool clock_out_get(ClockOutChannel_t ch, ClockOutBus_t clock_bus, uint32_t* freq_hz) {
    bool res = false;
    return res;
}

bool mco_init(void) {
    bool res = true;
    LOG_WARNING(CLK, "MCO Init..");

#ifdef HAS_MCO1
    res = mco_config(MCO_1, FREQ_SRC_PLL, 5);
#endif

#ifdef HAS_MCO2
    res = mco_config(MCO_2, FREQ_SRC_HSE, 5);
#endif

    return res;
}
