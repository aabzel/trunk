#ifndef NVIC_APP_DIAG_H
#define NVIC_APP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MCU_VENDOR_SPECIFIC_IRQ_NUM_DIAG \
{.name="FPU",    .int_n = 0, },    \
{.name="I2S0",    .int_n = 40, },


#ifdef __cplusplus
}
#endif

#endif /* NVIC_APP_DIAG_H  */
