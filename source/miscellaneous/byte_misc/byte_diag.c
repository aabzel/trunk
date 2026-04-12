#include "byte_diag.h"

const char* ByteNameToStr(const uint8_t code, const char* token) {
    char* name = "_";
    if(code) {
        name = token;
    }
    return name;
}
