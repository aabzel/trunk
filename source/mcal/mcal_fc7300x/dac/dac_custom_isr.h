#ifndef DAC_CUSTOM_ISR_H
#define DAC_CUSTOM_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool DacIRQHandler(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* DAC_CUSTOM_ISR_H */
