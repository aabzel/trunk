#ifndef IIR_DIAG_H
#define IIR_DIAG_H

#include <stdbool.h>
#include <stdint.h>

#include "iir_types.h"

bool iir_diag(void);
bool iir_diag_one(uint8_t num);
bool IirDiagCoefficient(uint8_t num);
const char* IirNodeToStr(const  IirHandle_t* const Node);
const char* IirConfigToStr(const  IirConfig_t* const Config);
bool iir_calc_frequency_response_norm(uint8_t num);
bool iir_calc_frequency_response(uint8_t num);

#endif /* IIR_DIAG_H */
