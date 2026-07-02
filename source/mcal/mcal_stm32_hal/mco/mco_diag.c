#include "mco_diag.h"

#include "mco_types.h"

const char* Freq2Str(FrequencySource_t freq) {
    const char* name = "?";
    switch(freq) {
    case FREQ_SRC_LSE:
        name = "LSE";
        break;
    case FREQ_SRC_HSE:
        name = "HSE";
        break;
    case FREQ_SRC_HSI:
        name = "HSI";
        break;
    case FREQ_SRC_PLL:
        name = "PLL";
        break;

    default:
        name = "??";
        break;
    }
    return name;
}
