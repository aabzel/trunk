#ifndef DECADRIVER_DIAG_H
#define DECADRIVER_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_DECADRIVER
#error "+ HAS_DECADRIVER"
#endif

#ifndef HAS_DECADRIVER_DIAG
#error "+HAS_DECADRIVER_DIAG"
#endif

#include "decadriver_types.h"

bool decadriver_diag(DecaDriverInstance_t* const Node);
const char* DecaErrToStr(int ret);

#ifdef __cplusplus
}
#endif

#endif /* DECADRIVER_DIAG_H */
