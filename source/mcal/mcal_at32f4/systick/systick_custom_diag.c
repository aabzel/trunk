#include "systick_custom_diag.h"

#include "common_diag.h"
#include "systick_types.h"

const char* SysTickCountFlag2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case 0:
        name = "Decrease";
        break;
    case 1:
        name = "Expired";
        break;
    }
    return name;
}

const char* SysTickClkSrc2Str(uint8_t code) {
    const char* name = "?";
    switch(code) {
    case 0:
        name = "AHB/8";
        break;
    case 1:
        name = "AHB";
        break;
    }
    return name;
}

const char* SysTickInt2Str(uint8_t code) { return OnOffToStr(code); }

const char* SysTickEn2Str(uint8_t code) { return OnOffToStr(code); }
