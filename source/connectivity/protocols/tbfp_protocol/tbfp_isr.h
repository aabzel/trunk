#ifndef TBFP_ISR_H
#define TBFP_ISR_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool tbfp_proc_byte_isr(uint8_t uart_num, uint8_t rx_byte);

#ifdef __cplusplus
}
#endif

#endif /* TBFP_ISR_H */
