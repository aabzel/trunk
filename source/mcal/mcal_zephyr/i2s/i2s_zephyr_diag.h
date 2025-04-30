
#ifndef I2S_DIAG_H
#define I2S_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_I2S
#error "It is needed HAS_I2S option for that component"
#endif

#ifndef HAS_DIAG
#error "It is needed HAS_DIAG option for that component"
#endif

#ifndef HAS_I2S_DIAG
#error "It is needed HAS_I2S_DIAG option for that component"
#endif

bool i2s_diag(uint8_t i2s_num);

#ifdef __cplusplus
}
#endif

#endif /* I2S_DIAG_H */
