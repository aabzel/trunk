#ifndef COMPLEX_MATH_DIAG_H
#define COMPLEX_MATH_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <complex.h>
#include <stdbool.h>
#include <stdint.h>


const char* ComplexToStr(double complex ComplexNumber);
bool complex_array_print(const double complex* const X, uint32_t len, double period_s, uint32_t order);

bool complex_array_print_csv(const double complex* const X, uint32_t len, double period_s, uint32_t order);
#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_MATH_DIAG_H */
