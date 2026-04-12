#ifndef DAC_CUSTOM_DIAG_H
#define DAC_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


bool dac_raw_reg_diag(uint8_t num);
bool dac_diag_custom(void);

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_DIAG_H */
