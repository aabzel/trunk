#include "float_diag.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "float_utils.h"
#include "log.h"
#include "shared_array.h"
#include "str_utils.h"

#ifdef HAS_RATIONAL_NUM
#include "rational_num.h"
#endif

#if 0
const char* FloatFixToStr(const FloatFixPoint_t* const Node) {
    static char lText[40] = {0};
    if(Node) {
        snprintf(lText, sizeof(lText), "%d.%u", Node->integer, Node->fractional);
    }
    return lText;
}
#endif

const char* FloatToStr(const float real_val, const uint32_t digit) {
    char* name = NULL;
    FloatFixPoint_t FixPoint = {0};
    bool res = float_to_integer_and_fractional(real_val, digit, &FixPoint);
    if(res) {
        name = (char*)FloatFixToStr(&FixPoint);
    }
    return name;
}

const char* FloatBigToStr(const float value) {
    float value_abs = fabsf(value);
    float order_d = log10f(value_abs);
    float mantissa = 0.0;
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case -15:
    case -14:
    case -13:
        mantissa = value * 1000000000000000.0f;
        snprintf(text, sizeof(text), "%7sf", FloatToStr(mantissa, 3));
        break;

    case -12:
    case -11:
    case -10:
        mantissa = value * 1000000000000.0f;
        snprintf(text, sizeof(text), "%7sp", FloatToStr(mantissa, 3));
        break;

    case -9:
    case -8:
    case -7:
        mantissa = VAL_TO_NANO_VAL(value);
        snprintf(text, sizeof(text), "%7sn", FloatToStr(mantissa, 3));
        break;

    case -6:
    case -5:
    case -4:
        mantissa = value * 1000000.0f;
        snprintf(text, sizeof(text), "%7su", FloatToStr(mantissa, 3));
        break;

    case -1:
        // snprintf(text, sizeof(text), "%7.2fd", value * 10.0);
        // break;
    case -2:
        // snprintf(text, sizeof(text), "%7.2fc", value * 100.0);
        // break;
    case -3:
        mantissa = value * 1000.0f;
        snprintf(text, sizeof(text), "%7sm", FloatToStr(mantissa, 3));
        break;

    case 0:
    case 1:
    case 2:
        mantissa = value;
        snprintf(text, sizeof(text), "%7s", FloatToStr(mantissa, 3));
        break;

    case 3:
    case 4:
    case 5:
        mantissa = value / 1000.0f;
        snprintf(text, sizeof(text), "%7sk", FloatToStr(mantissa, 3));
        break;

    case 6:
    case 7:
    case 8:
        mantissa = value / 1000000.0f;
        snprintf(text, sizeof(text), "%7sM", FloatToStr(mantissa, 3));
        break;

    case 9:
    case 10:
    case 11:
        mantissa = value / 1000000000.0f;
        snprintf(text, sizeof(text), "%7sG", FloatToStr(mantissa, 3));
        break;

    default:
        snprintf(text, sizeof(text), "%7s", FloatToStr(mantissa, 3));
        break;
    }

    str_del_char_inplace(text, ' ');
    LOG_DEBUG(SYS, "%f->[%s]", value, text);
    return text;
}
