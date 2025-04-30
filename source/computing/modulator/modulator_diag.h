#ifndef MODULATOR_DIAG_H
#define MODULATOR_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "modulator_types.h"

bool modulator_print_samples(Modulator_t* instance);

#ifdef __cplusplus
}
#endif

#endif /* MODULATOR_DIAG_H */
