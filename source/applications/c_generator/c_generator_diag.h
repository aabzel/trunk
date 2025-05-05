#ifndef C_GENERATOR_DIAG_H
#define C_GENERATOR_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "c_generator_types.h"

bool c_generator_diag(void);
bool cGeneratorDiag(const  cGeneratorHandle_t* const Node);
const char* cGeneratorDiag2Str(const cGeneratorHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* C_GENERATOR_DIAG_H */
