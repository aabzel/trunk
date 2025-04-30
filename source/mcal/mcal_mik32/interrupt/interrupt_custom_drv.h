#ifndef INTERRUPT_CUSTOM_DRIVER_H
#define INTERRUPT_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "mik32_hal.h"
#include "interrupt_custom_const.h"

bool interrupt_edge_ctrl(int16_t irq_n, bool on_off) ;
bool interrupt_level_control(int16_t irq_n, bool on_off) ;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPT_DRIVER_H  */
