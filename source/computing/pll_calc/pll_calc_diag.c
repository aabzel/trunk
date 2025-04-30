#include "pll_calc_diag.h"

#include <stdio.h>
#include <string.h>

const char* PllArtetyToStr(const PllArtety_t* const PllArtety) {
    static char name[80] = {0};
    if(PllArtety) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sExternalFreq:%u Hz", name, PllArtety->xtall_freq_hz);
#ifdef HAS_AT32F413
        snprintf(name, sizeof(name), "%sDiv:%1u,", name, PllArtety->pllhexdiv);
        snprintf(name, sizeof(name), "%sMult:%2u,", name, PllArtety->pllmult);
#endif
#ifdef HAS_AT32F43X
        snprintf(name, sizeof(name), "%sM:%2u,", name, PllArtety->ms);
        snprintf(name, sizeof(name), "%sN:%2u,", name, PllArtety->ns);
        snprintf(name, sizeof(name), "%sFR:%2u", name, PllArtety->fr);
#endif
        snprintf(name, sizeof(name), "%sCoreFreq:%u Hz", name, PllArtety->core_freq_hz);
    }
    return name;
}
