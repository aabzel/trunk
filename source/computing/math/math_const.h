#ifndef MATH_CONST_H
#define MATH_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI (3.14159)
#endif

typedef enum{
	DIGIT_INTEGER = 1,
	DIGIT_FRACTIONAL = 2,

	DIGIT_UNDEF= 0,
}DigitPart_t;

#ifdef __cplusplus
}
#endif

#endif /* MATH_CONST_H */
