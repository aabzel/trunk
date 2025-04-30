#ifndef CLOCK_CUSTOM_DIAG_H
#define CLOCK_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool clock_diag_low_level(void);
bool clock_diag_low_freq(void);
bool clock_diag_high_frequency(void);

#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_DIAG_H
