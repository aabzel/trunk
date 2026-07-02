#ifndef I2S_FULL_DUPLEX_ISR_H
#define I2S_FULL_DUPLEX_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "i2s_full_duplex_types.h"

/* ISR API*/

bool i2s_full_duplex_proc_input(uint8_t num, I2sFullDuplexInputs_t input);

/* settes*/

#ifdef __cplusplus
}
#endif

#endif /* I2S_FULL_DUPLEX_ISR_H */


