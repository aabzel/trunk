#include "float_diag.h"

#include <stdio.h>
#include <string.h>

#include "float_utils.h"
#include "shared_array.h"

char* FloatFixToStr(const FloatFixPoint_t* const Node, const uint32_t digit) {
    static char lText[40] = {0};
    if(Node) {
        (void)digit; // future use digits after dot
#if 0
        char format[40] = {0};
        strcpy(format,  "%%d.%%");
        snprintf(format, sizeof(format), "%s.%u", format, digit);
        snprintf(format, sizeof(format), "%su", format);
#endif
        snprintf(lText, sizeof(lText), "%d.%u", Node->integer, Node->fractional);
    }
    return lText;
}

char* FloatToStr(const float real_val, const uint32_t digit) {
    char* name = NULL;
    FloatFixPoint_t FixPoint = {0};
    bool res = float_to_integer_and_fractional(real_val, digit, &FixPoint);
    if(res) {
        name = FloatFixToStr(&FixPoint, digit);
    }
    return name;
}
