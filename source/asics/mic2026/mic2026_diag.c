#include "mic2026_diag.h"

const char* Mic2026ChanToStr(Mic2026Channel_t chan) {
    char* name = "?";
    switch((uint8_t)chan) {
    case CHANNEL_A:
        name = "A";
        break;
    case CHANNEL_B:
        name = "B";
        break;
    }
    return name;
}
