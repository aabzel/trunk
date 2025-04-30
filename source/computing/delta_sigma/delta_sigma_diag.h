#ifndef DELTA_SIGMA_DIAG_H
#define DELTA_SIGMA_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include  "delta_sigma_types.h"

bool delta_sigma_diag(uint8_t num);
const char* DeltaSigmaConfigToStr(const DeltaSigmaConfig_t* const Config);
const char* DeltaSigmaNodeToStr(const DeltaSigmaHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* DELTA_SIGMA_DIAG_H */
