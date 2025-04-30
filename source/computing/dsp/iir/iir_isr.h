#ifndef IIR_ISR_H
#define IIR_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iir_types.h"

bool iir_proc_in_out(uint8_t num, IirSample_t in_val, IirSample_t* const out_val);

#ifdef __cplusplus
}
#endif

#endif /* IIR_ISR_H */
