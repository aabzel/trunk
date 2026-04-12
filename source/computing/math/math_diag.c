#include "math_diag.h"

const char* MathParityToStr(const MathParity_t Parity) {
    char* name = "?";
    switch(Parity) {
    case MATH_PARITY_ODD:
        name = "odd";
        break;
    case MATH_PARITY_EVEN:
        name = "even";
        break;
    default:
        break;
    }
    return name;
}
