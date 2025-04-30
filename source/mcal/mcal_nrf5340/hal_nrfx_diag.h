#ifndef HAL_NRFX_DIAG_H
#define HAL_NRFX_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif
#include <nrfx.h>

#include "nrfx_errors.h"

const char* HalStatus2Str(nrfx_err_t code);

#ifdef __cplusplus
}
#endif

#endif /* HAL_NRFX_DIAG_H */
