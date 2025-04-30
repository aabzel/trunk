#ifndef NRF53_SYSTICK_H
#define NRF53_SYSTICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool systick_init(void);
bool systick_set_period_ms(uint32_t period_ms);
uint32_t systick_get_period_ms(void);

#ifdef __cplusplus
}
#endif

#endif // NRF53_SYSTICK_H
