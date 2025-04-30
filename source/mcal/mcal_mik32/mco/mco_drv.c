#include "mco_drv.h"

#include "log.h"
#include "mco_diag.h"
#include "mik32_hal.h"

uint32_t McoNum2McoHal(McoChannel_t chan) {
    uint32_t rcc_mco = 0;
    switch((uint8_t)chan) {
    case MCO_1:
        rcc_mco = RCC_MCO1;
        break;
    case MCO_2:
        rcc_mco = RCC_MCO2;
        break;
    }
    return rcc_mco;
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
