
#ifndef MAX98357_DIAG_H
#define MAX98357_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "max98357_types.h"

#ifndef HAS_MAX98357
#error "+HAS_MAX98357"
#endif

const char* Max98357DiagConfig(const Max98357Config_t* const Config);

#endif /* MAX98357_DIAG_H */
