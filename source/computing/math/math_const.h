#ifndef MATH_CONST_H
#define MATH_CONST_H


#include <math.h>

#ifndef M_PI
#define M_PI (3.14159)
#endif

typedef enum{
    DIGIT_INTEGER = 1,
    DIGIT_FRACTIONAL = 2,
    DIGIT_UNDEF= 0,
}DigitPart_t;

typedef enum {
    MATH_PARITY_ODD = 1, /* not devided by 2*/
    MATH_PARITY_EVEN = 2, /*devided by 2*/
    MATH_PARITY_UNDEF = 0,
}MathParity_t;


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#define M_2PI (M_PI*2.0)



#endif /* MATH_CONST_H */
