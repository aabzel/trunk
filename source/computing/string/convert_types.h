#ifndef CONVERT_TYPES_H
#define CONVERT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "convert_const.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    double value;
    double mantissa;
    double exponenta;
    char cur_letter;
    int8_t sign;
    long double integer ; /*uint64_t integer */
    uint32_t fraction_order;
    double fraction ;
    ParseNumberStates_t state;
    bool spot_mantissa;
    bool spot_exponent;
    int8_t exponent_sign; /*-1 or 1 */
    uint32_t exponent_integer;
}Text2NumberFsm_t;

#ifdef __cplusplus
}
#endif

#endif /* CONVERT_TYPES_H */
