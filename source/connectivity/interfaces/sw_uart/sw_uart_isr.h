#ifndef SW_UART_ISR_H
#define SW_UART_ISR_H

#ifdef __cplusplus
extern "C" {
#endif


#include "std_includes.h"
#include "sw_uart_config.h"
#include "sw_uart_types.h"

bool sw_uart_proc_event(uint8_t num, uint8_t part_num);

#ifdef __cplusplus
}
#endif

#endif /* SW_UART_ISR_H */
