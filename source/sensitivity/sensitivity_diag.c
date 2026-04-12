#include "sensitivity_diag.h"

#include "sensitivity_const.h"

const char* UnitsToStr(const Units_t units) {
    const char* name = "?";
    switch(units) {
    case UNITS_METER:        name = "m";        break;
    case UNITS_UVI:        name = "uvi";        break;
    case UNITS_LUX:        name = "lux";        break;
    case UNITS_VOLT:        name = "V";        break;
    case UNITS_RADIAN:        name = "Rad";        break;
    default:        name = "?";        break;
    }
    return name;
}
