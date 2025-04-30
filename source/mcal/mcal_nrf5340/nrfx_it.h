
#ifndef NRFX_IT_H
#define NRFX_IT_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef	HAS_SYSTICK
#include "systick_general.h"
#endif


#ifdef HAS_SOFTWARE_TIMER
#include "software_timer_isr.h"
#endif /*HAS_SOFTWARE_TIMER*/

#ifdef HAS_I2S
#include "nrfx_i2s.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif


#ifdef __cplusplus
}
#endif

#endif /* NRFX_IT_H */
