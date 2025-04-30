#ifndef MCO_DIAG_H
#define MCO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "mco_types.h"

const char* Freq2Str(FrequencySource_t freq);

#ifdef __cplusplus
}
#endif

#endif /* MCO_DIAG_H */
