#ifndef SYSTICK_CORE_H
#define SYSTICK_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_SYSTICK_CUSTOM
#include "systick_custom.h"
#endif /*HAS_SYSTICK_CUSTOM*/

#ifdef HAS_CORE_APP
#include "nrf5340_application.h"
#endif

#ifdef HAS_CORE_NET
#include "nrf5340_network.h"
#endif

#include "systick_types.h"

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

bool systick_disable(void);
bool systick_general_set_clksrc(ClkSrc_t clksrc);
bool systick_general_set_load(uint32_t new_load);
bool systick_general_is_run(void);
bool systick_general_stop(void);
bool systick_general_start(void);
bool systick_init(void);
bool systick_general_init(uint32_t base_addr, uint32_t clk);
bool systick_set_period_s(uint32_t systick_clock_hz, double period_s);
bool systick_set_load(uint32_t load);
double systick_general_get_period(uint32_t systick_clock_hz);
void SysTickIntHandler(void);
uint32_t systick_general_get_load(void);
uint32_t systick_general_get_ms(void);
uint64_t systick_general_get_us(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTICK_CORE_H
