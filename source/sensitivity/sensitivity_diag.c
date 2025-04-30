#include "sensitivity_diag.h"

const char* UnitsToStr(Units_t units) {
    const char* name = "?";
    switch(units) {
    case UNITS_METER:
        name = "m";
        break;
    case UNITS_UVI:
        name = "uvi";
        break;
    case UNITS_LUX:
        name = "lux";
        break;
    case UNITS_VOLTS:
        name = "V";
        break;
    case UNITS_RADIANS:
        name = "Rad";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}
