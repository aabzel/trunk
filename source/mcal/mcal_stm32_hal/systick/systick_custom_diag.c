#include "systick_custom_diag.h"

#include "common_diag.h"
#include "systick_types.h"

const char* SysTickCountFlagToStr(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case 0:
        name = "Decrease";
        break;
    case 1:
        name = "Expired";
        break;
    default:
        break;
    }
    return name;
}

const char* SysTickClkSrcToStr(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case 0:
        name = "AHB/8";
        break;
    case 1:
        name = "AHB";
        break;
    default:
        break;
    }
    return name;
}

const char* SysTickIntToStr(uint8_t code) { return OnOffToStr(code); }

const char* SysTickEnToStr(uint8_t code) { return OnOffToStr(code); }
