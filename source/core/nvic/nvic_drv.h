#ifndef NVIC_MCAL_H
#define NVIC_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "nvic_types.h"
#include "microcontroller.h"
#ifdef HAS_NVIC_DIAG
#include "nvic_diag.h"
#endif

bool nvic_clear(void);
bool nvic_init(void);
bool nvic_irq_ctrl(int16_t irq_n, const bool on_off);
bool nvic_ctrl(const bool on_off);
bool nvic_disable(void);
bool nvic_is_valid_irq_num(int16_t irq_n);

#ifdef __cplusplus
}
#endif

#endif /* NVIC_MCAL_H  */
