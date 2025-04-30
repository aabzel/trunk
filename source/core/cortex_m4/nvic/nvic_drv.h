#ifndef NVIC_DRV_H
#define NVIC_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "nvic_types.h"
#include "microcontroller_types.h"

#ifdef HAS_EHAL
#include "miscellaneous_ehal.h"
#endif

#ifdef HAS_CMSIS
//#include "core_cm4.h"
#endif

bool nvic_clear(void);
bool nvic_disable(void);
bool nvic_init(void);
bool nvic_is_valid_irq_num(int16_t irq_n);

#ifdef __cplusplus
}
#endif

#endif /* NVIC_DRV_H  */
